/*
code for the second project of VG100 in UMJI, 2017 FALL
@makersmelx


/*
BUG index：
  BUG1 : 时间种子能否使用 //直接GG
  BUG2 : 猜测——按钮按下去时是 digitalread（。。。。）==HIGH 执行相关函数  但无法使该函数只运行一次。

*/

/*
For lab teacher
每局游戏开始前讲1-12随机排序，取前八个作为一个数组A
第N次kick，取A[N-1]作为这次踢的门的编号。并定义这个门周围的几个门的不同性质（门的分数和后续事件）
被踢的时候根据触发的门数量和门的性质计算该次kick的分数，并结束这次kick
如果10s没踢，也结束这次kick



*/
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Goal.h>
//#include <time.h>//BUG1

int ButtonPin[12] = {21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};
int LedPin[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int ResetButtonPin = 33;

int ResetButtonState = 0;
boolean reset_pressed = false ; 


int random_order[8];
int temp_change;

unsigned long time_new_game_start = 0;
unsigned long time_new_kick_start = 0;
unsigned long time_this_kick_end = 0;
unsigned long time_now = 0;

int trial = 0;
int this_turn_goal;
int part_hit = 0;
int score = 0;
int total_score = 0;
int temp_closed[4] = {-1, -1, -1, -1};
int temp_corner[4] = {-1, -1, -1, -1};
int length_temp_closed;
int length_temp_corner;
boolean one_kick_finish = false;

//int random(int min, int max){
////    srand(time(NULL)); //BUG1
//    int temp;
//    temp = rand() % (max - min + 1) + min;
//    return temp;
//  }

Goal goal[12];
Adafruit_7segment score_board;

void setup()
{
#ifndef __AVR_ATtiny85__
  Serial.begin(57600);
#endif
  score_board.begin(0x70);
  for (int i = 0; i <= 11; i++)
  {
    goal[i].get_goal_id(i);
    goal[i].get_button_pin(*(ButtonPin+i));
    goal[i].get_led_pin(*(LedPin + i));
    goal[i].goal_setup();
    pinMode(ResetButtonPin,INPUT);
  }
}

void loop()
{

  ResetButtonState = digitalRead(ResetButtonPin);
  for (int i = 0; i <= 11; i++)
    goal[i].button_state = digitalRead(goal[i].button_pin);

  if (HIGH == ResetButtonState && !reset_pressed)
  {
    reset_pressed = true ;
    Serial.println("Reset");
    for (int i = 0; i <= 11; i++)
      goal[i].button_state = 0;
    time_new_game_start = millis();
    time_this_kick_end = millis();
    // randomSeed(time_new_game_start); 这个感觉有问题，先注释掉了
    int temp_num[12];
    for (int i = 0; i <= 11; i++)
      temp_num[i] = i+1;
    for (int i = 0; i <= 11; i++)
    {
      int temp_random = random(i,11);
      temp_change = *(temp_num + i);
      *(temp_num + i) = *(temp_num + temp_random);//随机交换i项和i~11中一项
      *(temp_num + temp_random) = temp_change;
    }

    for (int i = 0; i < 7; i++)
    {
      random_order[i] = *(temp_num + i);
      Serial.print(random_order[i]); //11/24一直输入重复的数字
      Serial.print(" ");
    }
    Serial.println("");
    trial = 0;
    this_turn_goal = random_order[trial];
    score = 0;
    one_kick_finish = false;
  }

   

  if (one_kick_finish) //end part
  {
    goal[this_turn_goal].end_work();

    score_board.print(score);
    score_board.writeDisplay();
    delay(1250);
    /**********************************/
    time_this_kick_end = millis();
    trial++;
    this_turn_goal = *(random_order + trial);

    goal[this_turn_goal].chosen_button_work();

    for (int i = 0; i <= 3; i++)
    {
      int j = 0;
      if (goal[this_turn_goal].define_closed_button(i + 1) != 100)
      {
        temp_closed[j] = goal[this_turn_goal].define_closed_button(i + 1);
        j++;
      }
    }
    for (int i = 0; i <= 3; i++)
    {
      int j = 0;
      if (goal[this_turn_goal].define_corner_button(i + 1) != 100)
      {
        temp_corner[j] = goal[this_turn_goal].define_corner_button(i + 1);
        j++;
      }
    }

    score = 0;
  }
  time_new_kick_start = time_this_kick_end;
  goal[this_turn_goal].chosen_button_work();
  for (int i = 0; i <= 3; i++)
  {
    int j = 0;
    if (goal[this_turn_goal].define_closed_button(i + 1) != 100)
    {
      temp_closed[j] = goal[this_turn_goal].define_closed_button(i + 1);
      j++;
    }
  }

  for (int i = 0; i <= 3; i++)
  {
    int j = 0;
    if (goal[this_turn_goal].define_corner_button(i + 1) != 100)
    {
      temp_corner[j] = goal[this_turn_goal].define_corner_button(i + 1);
      j++;
    }
  }


  for(int i =1 ; i<=12; i++){
    goal[i].zero_button_work();
  }
  // length_temp_closed = sizeof(temp_closed) / sizeof(temp_closed[0]);
  // length_temp_corner = sizeof(temp_corner) / sizeof(temp_corner[0]);

  for (int i = 0; i <= 3; i++)
  {
    if (*(temp_closed + i) != -1)
    {
      goal[temp_closed[i]].closed_button_work();
      goal[temp_closed[i]].button_hit();
    }

    if (*(temp_corner + i) != -1)
    {
      goal[temp_corner[i]].corner_button_work();
      goal[temp_corner[i]].button_hit();
    }
  }

  for (int i = 0; i <= 11; i++)
  {
    if (goal[i].activated && !goal[i].hit_then_zero)
    {
      part_hit++;
      score = score + goal[i].target_value;
    }
  }
  for (int i = 0; i <= 11; i++)
  {
    if (goal[i].activated && goal[i].hit_then_zero)
    {
      score = 0;
    }
  }
//kick结束算分部分
  part_hit = min(part_hit, 3);
  score = score / part_hit;
  total_score = total_score + score;

  //end part (score and ready for next)
  for (int i = 0; i <= 11; i++)
  {
    if (goal[i].activated)
    {
      one_kick_finish = true;
      break;
    }
  }

  time_now = millis();
  if (time_now - time_new_kick_start > 10000)
    one_kick_finish = true;

  if (trial == 7)
  {
    delay(750);
    score_board.print(score);
    score_board.writeDisplay();
    delay(1000);
    score_board.print(total_score);
    score_board.writeDisplay();
    delay(3000);
  }
}
