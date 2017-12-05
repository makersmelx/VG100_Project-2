
#include <Goal.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

ptrdiff_t myrandom(ptrdiff_t i) { return rand() % i; }
ptrdiff_t (*p_myrandom)(ptrdiff_t) = myrandom;

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

int *get_random_order(int num, int take)
{
  srand(unsigned(time(NULL)));
  vector<int> myvector;
  vector<int>::iterator it;
  int order[8];
  // set some values:
  for (int i = 0; i < num - 1; i++)
    myvector.push_back(i);

  // using built-in random generator:
  random_shuffle(myvector.begin(), myvector.end());

  // using myrandom:
  random_shuffle(myvector.begin(), myvector.end(), p_myrandom);

  myvector.erase(take, num - 1);
  for (it = myvector.begin(); it != myvector.end(); ++it)
    order[it] = *it;
  return order;
}

Goal goal[12];

void setup()
{

  for (int i = 0; i <= 11; i++)
  {
    goal[i].get_goal_id(i);
    goal[i].get_button_pin(ButtonPin[i]);
    goal[i].get_led_pin(LedPin[i]);
    goal[i].goal_setup();
    pinMode(ResetButtonPin, INPUT);
  }
  random_order = get_random_order(12，8);
}

void loop()
{

  ResetButtonState = digitalRead(ResetButtonPin);

  if (ResetButtonState == HIGH)
  {
    for (int i = 0; i <= 7; i++)
      random_order[i] = 0;
    random_order = get_random_order(12，8);
    trial = 0;
    score = 0;
    one_kick_finish = false;
    goal[random_order[trial]].chosen_button_work();
    temp_closed = goal[random_order[trial]].define_closed_button();
    temp_corner = goal[random_order[trial]].define_corner_button();
  }

  length_temp_closed = sizeof(temp_closed) / sizeof(temp_closed[0]);
  length_temp_corner = sizeof(temp_corner) / sizeof(temp_corner[0]);

  for (int i = 0; i <= length_temp_closed, i++)
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
    if (goal[i].hit_then_zero)
      score = 0;
    part_hit = min(part_hit, 3);
    score = score / part_hit;
  }

  //kick finish and total score not written yet

  //end part (score and ready for next)
  if (one_kick_finish)
  {
    trial++;
    goal[random_order[trial]].chosen_button_work();
    temp_closed = goal[random_order[trial]].define_closed_button(); //改指针~
    temp_corner = goal[random_order[trial]].define_corner_button();
    score = 0;
    one_kick_finish = false;
    delay(1250);
  }
}
