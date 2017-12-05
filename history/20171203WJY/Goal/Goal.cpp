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

// void Goal::set_hit_then_zero(int loc)
// {
//     const int X_DIR[] = {1, 1, -1, 1, 0, 0, -1, -1, 0};
//     const int Y_DIR[] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
//     const int SCORE[] = {40, 40, 70, 70, 70, 70, 40, 40, 100};
    

//     for (int i = 0; i < 9; ++i)
//     {
//         int x = get_x(loc) + X_DIR[i];
//         int y = get_y(loc) + Y_DIR[i];
//         if (x > 0 && x <= 3 && y > 0 && y <= 4)
//         {
//             int l = 4 * (x - 1) + y;
//             goal[l].hit_then_zero = false;
//             goal[l].target_value = SCORE[i];
//         }
//     }
// }



// void Goal::all_goal_work(int center)
// {
    // goal[center].led_work(true);
    // for (int i = 1; i <= 12; i++)
    // {
    //     goal[i].button_work();
    // }
// }