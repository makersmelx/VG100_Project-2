#include "Goal.h"
// #include "utility.h"
// #include "iostream.h"

std::pair<int, int> Football::getPos(int loc)
{
    int x = (loc - 1) / 4 + 1;
    int y = (loc - 1) % 4 + 1;
    return {x, y};
}

void Football::set_hit_then_zero(int loc)
{
    const int X_DIR[] = {1,1,-1,1,0,0,-1,-1,0};
    const int Y_DIR[] = {1,-1,0,0,-1,1,1,-1,0};
    const int SCORE[] = {40,40,70,70,70,70,40,40,100};
    std::pair<int, int> pos = getPos(loc);
    
    for(int i=1;i<=12;++i) 
    {
        goal[i].hit_then_zero = true;
        goal[i].score = 0;
    }

    for(int i=0;i<9;++i)
    {
        int x = pos.first + X_DIR[i];
        int y = pos.second + Y_DIR[i];
        if (x>0 && x<=3 && y>0 && y<=4)
        {
            int l = 4 * (x - 1) + y;
            goal[l].hit_then_zero = false;
            goal[l].score = SCORE[i];
        }
    }
}

void Football::setup_goal(int button, int led)
{
    pinMode(led,OUTPUT);
    pinMode(button,INPUT);
}


void Football::set_default()
{
    for(int i = 1; i<=12,i++)
        {
            goal[i].score = 0;
            goal[i].hit_then_zero = true ;
        }
}

void Football::goal_work(int center)
{   
    goal[center].led_work(true);

    for (int i =1 , i <= 12,i++)
    {
        goal[i].button_work();  
    }
}

void Goal::set_button_pin(int b_pin)
{
    button_pin = b_pin;
}

void Goal::set_led_pin(int l_pin)
{
    led_pin = l_pin;
}

void Goal:led_work(bool a)
{
    if(a)
        digitalWrite(led_pin,HIGH);
    if(!a)
        digitalWrite(led_pin,LOW);
}

void Goal::button_work()
{
    if (button_state == HIGH)
    {
        activated = true;
    }
    else
    {
        activated = false;
    }
}



// int main()
// {
//     Football a;
//     for(int i=1;i<=12;++i) 
//     {
//         std::cout << i << "\t";
//         a.set_hit_then_zero(i);
//         std::cout << std::endl;
//     }
//     //std::cin.get();
// }
