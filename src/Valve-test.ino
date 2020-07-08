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

//single valve 
#define VALVE_PIN 2

//duble valve
#define VALVE_PIN_1 2
#define VALVE_PIN_1 3

//sensor type for valve Feedback
/* 
you can use this type of sensor
: temprature sensor 
: flow sensor
: presser sensor
: flame sensor
*/

#define TEMPRATURE_SENSOR 4
#define FLOW_SENSOR 4
#define PRESSUER_SENSOR 4
#define FLAME_SENSOR 4

void setup()
{
    pinMode(VALVE_PIN,OUTPUT);

    pinMode(VALVE_PIN_1,OUTPUT);
    pinMode(VALVE_PIN_2,OUTPUT);

    pinMode(TEMPRATURE_SENSOR,INPUT);
    pinMode(FLOW_SENSOR,INPUT);
    pinMode(PRESSUER_SENSOR,INPUT);
    pinMode(FLAME_SENSOR,INPUT);
}

void loop()
{
    
}