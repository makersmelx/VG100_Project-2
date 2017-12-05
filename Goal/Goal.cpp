#THIS FILE IS PART OF Project 2 of VG100 in 2017 FALL by Group 13
#Goal.cpp --- This is the code of the library Goal that is used in the core code 
#THIS PROGRAM IS FREE for everyone
#Copyright(c) 2017 makersmelx

#include"Arduino.h"
#include"Goal.h"


Goal::Goal()
{
}

void Goal::get_goal_id(int num)
{
    goal_id = num;
}

void Goal::get_button_pin(int b_pin)
{
    button_pin = b_pin;
}

void Goal::get_led_pin(int l_pin)
{
    led_pin = l_pin;
}

void Goal::goal_setup()
{
    pinMode(button_pin,INPUT);
    pinMode(led_pin,OUTPUT);
    button_state = 0;
}

void Goal::button_work(){
    if(hit_then_zero)
        target_value = 0;
    if (button_state == HIGH)
    {
        activated = true;
    } 
    else
    {
        activated = false;
    }      
    
}

void Goal::led_work(bool a){
    if(!a)
        digitalWrite(led_pin,LOW);
    if(a)
        digitalWrite(led_pin, HIGH);
}

int Goal::get_x(int loc)
{
    int x = (loc - 1) / 4 + 1;
    return x;
}

int Goal::get_y(int loc)
{
     int y = (loc - 1) % 4 + 1;
     return y;
}
