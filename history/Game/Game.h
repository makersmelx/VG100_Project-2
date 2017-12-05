#ifndef Game_h
#define Game_h

#include "Arduino.h"


class Goal
{
  private:
    
    

  public:
    friend class Football;

    int score = 0;
    int button_state = 0;
    int button_pin = 0;
    int led_pin=0;

    bool hit_then_zero = true;
    bool activated = false;

    void set_button_pin(int b_pin);
    void set_led_pin(int l_pin);
    void led_work(bool a);
    void button_work();
};

class Football
{
  private:
    
    std::pair<int, int> getPos(int loc);

  public:
    Goal goal[13];
    void set_default();
    void set_hit_then_zero(int loc);
    void setup_goal(int button, int led);
    void goal_work(int center);

    int trial =1;


    
    

};


#endif