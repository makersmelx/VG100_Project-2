
#include <Goal.h>


int ButtonPin[12] = {};
int ResetButtonPin;
int ResetButtonState = 0;
int LedPin[12] = {};


int *random_order;
int trial = 0;
int part_hit = 0;
int score;
int total_score;
int *temp_closed;
int *temp_corner;
int length_temp_closed;
int length_temp_corner;
boolean one_kick_finish = false;

int* get_random_order(int num, int take)
{
  int temp_num[];
  for (i = 1; i<= num; i++)
    temp_num[i] = i;
  for (i = 0; i <= num -1; i++)
    swap(temp_num[i], temp_num(random(i,num-1)));
  return temp_num;
}

Goal goal[12];


void setup() {

  for (int i = 0; i <= 11; i++)
  {
    goal[i].get_goal_id(i);
    goal[i].get_button_pin(ButtonPin[i]);
    goal[i].get_led_pin(LedPin[i]);
    goal[i].goal_setup();
    pinMode(ResetButtonPin,INPUT);
  }
}

void loop() {

  ResetButtonState = digitalRead(ResetButtonPin);

  if(ResetButtonState == HIGH)
  {
    for (int i = 0; i <= 7; i++)
      random_order[i] = 0;
    random_order = get_random_order();
    trial = 0;
    score = 0;
    one_kick_finish = false;
    goal[random_order[trial]].chosen_button_work();
    temp_closed = goal[random_order[trial]].define_closed_button();
    temp_corner = goal[random_order[trial]].define_corner_button();
  }
  
  length_temp_closed = sizeof(temp_closed) / sizeof(temp_closed[0]);
  length_temp_corner = sizeof(temp_corner) / sizeof(temp_corner[0]);

  for(int i = 0; i <= length_temp_closed, i++)
    goal[temp_closed[i]].closed_button_work();

  for (int i = 0; i <= length_temp_corner, i++)
    goal[temp_corner[i]].corner_button_work();

  for (int i = 0; i <= 11; i++)
    {
      if (goal[i].activated && !goal[i].hit_then_zero)
      {
        part_hit++;
        score = score + goal[i].target_value;
      }
      if(goal[i].hit_then_zero)
        score = 0;
      part_hit = min(part_hit , 3);  
      score = score / part_hit;
    }
  
 
  //kick finish and total score not written yet

  //end part (score and ready for next)
  if (one_kick_finish)
  {
    trial++;
    goal[random_order[trial]].chosen_button_work();
    temp_closed = goal[random_order[trial]].define_closed_button();//改指针~
    temp_corner = goal[random_order[trial]].define_corner_button();
    score = 0;
    one_kick_finish = false;
    delay(1250);
  }
}
  




