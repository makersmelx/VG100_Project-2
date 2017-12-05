#THIS FILE IS PART OF Project 2 of VG100 in 2017 FALL by Group 13
#Goal.cpp-- - This is the header of the library Goal that is used in the core code
#THIS PROGRAM IS FREE for everyone
#Copyright(c) 2017 makersmelx

#ifndef Goal_h
#define Goal_h

class Goal
{
public:
    Goal();
    int goal_id = 0;
    int button_pin = 0;
    int button_state = 0;
    int led_pin =0;

    int target_value=0;
    bool hit_then_zero=true;
    bool activated=false;

    void get_goal_id(int num);
    void get_button_pin(int b_pin);
    void get_led_pin(int l_pin);
    void goal_setup();

    void set_goal_value();
    int get_x(int loc);
    int get_y(int loc);
    void set_hit_then_zero(int loc);

    void button_work();
    void led_work(bool a);
    void all_goal_work(int center);   
};
#endif