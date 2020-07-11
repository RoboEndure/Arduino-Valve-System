#include "Arduino.h"

/*
Details of 
where to use valve 
what use of valve
Liquid 0r Gas
Feedback system
etc
every littel details about valve use

this code file is only for single feedback sensor 
you can modify if know ablut multi feedback

there is no responsibilty for your hardware 
so change when you know this not damage your hardware 

*/


//select onlyone valve system

#define VALVE_SINGLE true

//#define VALVE_DOUBLE true

//#define MOTOR_STEPPER true

//#define MOTOR_SERVO_MINI true

//#define MOTOR_DC true



//select sensor type

#define ANALOG_SENSOR 1      //sensor output is analog then select this type sensor 

//#define DIGITAL_SENSOR 1   //sensor output is digital then select this type sensor 



#if ANALOG_SENSOR
    #define ANALOG_INPUT A0//select pin for analog sensor input
    #define INPUT_VALUE ANALOG_INPUT
#elif DIGITAL_SENSOR 
    #define DIGITAL_INPUT 1
    #define DIGITAL_MIN_INPUT 1   //value in digits so, dont change until you know ablut your sensor default value
    #define DIGITAL_MAX_INPUT 100
    #define INPUT_VALUE DIGITAL_INPUT
#endif


/*
    which type valve system you want to use 
    and there is CONSTANT & NON_CONSTANT system
    which look at your valve application
    so take care of that things 
    so be carefull when you use skech like this
*/
//single valve 
#if VALVE_SINGLE
    #define NON_CONSTANT 1
    #define VALVE_PIN 2
#elif VALVE_DOUBLE
//duble valve
    #define CONSTANT 1
    #define VALVE_PIN_1 2
    #define VALVE_PIN_1 3
#elif MOTOR_STEPPER
    #define CONSTANT 1
    #define STEP_PIN 2
    #define DIRC_PIN 3
#elif MOTOR_SERVO_MINI
    #define CONSTANT 1
    #define PULSE_PIN 2
#elif MOTOR_DC
    #define CONSTANT 1
    #define STEP_PIN 2
    #define DIRC_PIN 3
#endif



//do not change this value C'oz this work on which type valve system
//you selected
#if NON_CONSTANT
    #define RELAY_TYPE 1
#elif CONSTANT
    #define MIN_VALUE 0
    #define MAX_VALUE 100
#endif



//#define ANALOG_INPUT A0//use for single pin analog input sensor



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
    input_value();                //read from selected sensor system
    output = computePID(input);            //calculate PID using selected system configuration 
    delay(100);                            //gap between two loop


    analogWrite(3, output);                //control the valve based on PID value or motors
}



void input_value()
{
    #if ANALOG_SENSOR
        input = analogRead(INPUT_VALUE);
    #elif DIGITAL_SENSOR
        input = digitalCalibration();
    #endif
}



int digitalCalibration()
{
    #define MAX_ANALOG 1023
    #ifdef DIGITAL_SENSOR
        INPUT_VALUE = ((DIGITAL_MAX_INPUT * DIGITAL_INPUT) / MAX_ANALOG);
        return INPUT_VALUE; 
    #endif
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