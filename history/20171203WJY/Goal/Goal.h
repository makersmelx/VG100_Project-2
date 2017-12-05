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

    
    void button_work();
    void led_work(bool a);

    void set_goal_value();
    void set_hit_then_zero(int loc);
    void all_goal_work(int center);

    int get_x(int loc);
    int get_y(int loc);

  private:
    
};

// class Football
// {
// public:
//     Goal goal[13];
    

//   private:
    
// };













#endif