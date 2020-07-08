#include "Arduino.h"

/*
Details of 
where to use valve 
what use of valve
Liquid 0r Gas
Feedback system
etc
every littel details about valve use
*/

//select valve system
#define VALVE_SINGLE true
//#define VALVE_DOUBLE true

//select sensor system
#define TEMPRATURE_SENSOR true
//#define FLOW_SENSOR true
//#define PRESSUER_SENSOR true
//#define FLAME_SENSOR true

//single valve 
#if VALVE_SINGLE
#define VALVE_PIN 2
#elif VALVE_DOUBLE
//duble valve
#define VALVE_PIN_1 2
#define VALVE_PIN_1 3
#endif

//sensor type for valve Feedback
/* 
you can use this type of sensor
: temprature sensor 
: flow sensor
: presser sensor
: flame sensor
*/
#if TEMPRATURE_SENSOR
#define TEMPRATURE_SENSOR 4
#elif FLOW_SENSOR
#define FLOW_SENSOR 4
#elif PRESSUER_SENSOR
#define PRESSUER_SENSOR 4
#elif FLAME_SENSOR
#define FLAME_SENSOR 4
#endif

//variable define here 
double kp = 2;
double ki = 5;
double kd = 1;
 
unsigned long currentTime, previousTime;
double elapsedTime;
double error;
double lastError;
double input, output, setPoint;
double cumError, rateError;

//details about PID 
//setPoint = 0;

void setup()
{   
    setPoint = 0;

    #if VALVE_SINGLE
    pinMode(VALVE_PIN,OUTPUT);
    #elif VALVE_DOUBLE
    pinMode(VALVE_PIN_1,OUTPUT);
    pinMode(VALVE_PIN_2,OUTPUT);
    #endif

    #if TEMPRATURE_SENSOR
    pinMode(TEMPRATURE_SENSOR,INPUT);
    #elif FLOW_SENSOR
    pinMode(FLOW_SENSOR,INPUT);
    #elif PRESSUER_SENSOR
    pinMode(PRESSUER_SENSOR,INPUT);
    #elif FLAME_SENSOR
    pinMode(FLAME_SENSOR,INPUT);
    #endif
}

void loop()
{
    input = analogRead(A0);                //read from rotary encoder connected to A0
    output = computePID(input);
    delay(100);
    analogWrite(3, output);                //control the motor based on PID value
}

double computePID(double inp)
{     
    currentTime = millis();                                     //get current time
    elapsedTime = (double)(currentTime - previousTime);         //compute time elapsed from previous computation
    
    error = setPoint - inp;                                     // determine error
    cumError += error * elapsedTime;                            // compute integral
    rateError = (error - lastError)/elapsedTime;                // compute derivative

    double out = kp*error + ki*cumError + kd*rateError;         //PID output               

    lastError = error;                                          //remember current error
    previousTime = currentTime;                                 //remember current time

    return out;                                                 //have function return the PID output
}