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

// #define CONSTANT 
// #define NON_CONSTANT

//select onlyone valve system
#define VALVE_SINGLE true
//#define VALVE_DOUBLE true
//#define MOTOR_STEPPER true
//#define MOTOR_SERVO_MINI true
//#define MOTOR_DC true

//select sensor system
#define TEMPRATURE_SENSOR true
//#define FLOW_SENSOR true
//#define PRESSUER_SENSOR true
//#define FLAME_SENSOR true

//single valve 
#if VALVE_SINGLE
#define NON_CONSTANT
#define VALVE_PIN 2
#elif VALVE_DOUBLE
//duble valve
#define CONSTANT 
#define VALVE_PIN_1 2
#define VALVE_PIN_1 3
#elif MOTOR_STEPPER
#define CONSTANT 
#define STEP_PIN 2
#define DIRC_PIN 3
#elif MOTOR_SERVO_MINI
#define CONSTANT 
#define PULSE_PIN 2
#elif MOTOR_DC
#define CONSTANT 
#define STEP_PIN 2
#define DIRC_PIN 3
#endif

#define ANALOG_INPUT A0//use for single pin analog input sensor

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
int sensor_value = 0;

//sensor type for valve Feedback
/* 
you can use this type of sensor
: temprature sensor 
: flow sensor
: presser sensor
: flame sensor
*/
#if TEMPRATURE_SENSOR
#define TEMPRATURE_SENSOR
#elif FLOW_SENSOR
#define FLOW_SENSOR 
#elif PRESSUER_SENSOR
#define PRESSUER_SENSOR 
#elif FLAME_SENSOR
#define FLAME_SENSOR 
#endif

void setup()
{   
    setPoint = 0;

    #if VALVE_SINGLE
    pinMode(VALVE_PIN,OUTPUT);
    #elif VALVE_DOUBLE
    pinMode(VALVE_PIN_1,OUTPUT);
    pinMode(VALVE_PIN_2,OUTPUT);
    #elif VALVE_DOUBLE
    pinMode(STEP_PIN,OUTPUT);
    pinMode(DIRC_PIN,OUTPUT);
    #elif
    pinMode(PULSE_PIN,OUTPUT);
    #elif VALVE_DOUBLE
    pinMode(STEP_PIN,OUTPUT);
    pinMode(DIRC_PIN,OUTPUT);
    #endif

    
}

void loop()
{
    input = analogRead(ANALOG_INPUT);                //read from selected sensor system
    output = computePID(input);            //calculate PID using selected system configuration 
    delay(100);                            //gap between two loop


    analogWrite(3, output);                //control the valve based on PID value or motors
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