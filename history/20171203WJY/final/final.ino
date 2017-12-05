/*
code for the second project of VG100 in UMJI, 2017 FALL
@makersmelx


/*
BUG index：
  BUG1 : 时间种子能否使用 //直接GG
  BUG2 : 猜测——按钮按下去时是 digitalread（。。。。）==HIGH 执行相关函数  但无法使该函数只运行一次。

*/

/*
注意：这块板的数组没有[0]


*/
#include <Wire.h> 
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Goal.h>
//#include <time.h>//BUG1

int ButtonPin[13] = {0,24, 23, 22, 40, 28, 27, 26, 25, 42, 31, 30, 29};
int LedPin[13] = {0,4, 3, 2, 41, 8, 7, 6, 5, 12, 11, 10, 9};
int ResetButtonPin = 45;
int ResetButtonState = 0;

const int X_DIR[] = {1, 1, -1, 1, 0, 0, -1, -1, 0};
const int Y_DIR[] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
const int SCORE[] = {40, 40, 70, 70, 70, 70, 40, 40, 100};



int random_order[9];
int temp_change = 0;

unsigned long time_new_kick_start = 0;
unsigned long time_now = 0;

int trial = 1;
int this_turn_goal =0;
int part_hit = 0;
int score = 0;
int total_score = 0;

bool one_kick_finish = false;
bool game_start = false;
bool wait_for_button = false;
bool value_set = false;


Goal goal[13];
Football this_game;
Adafruit_7segment score_board;

void setup()
{
#ifndef __AVR_ATtiny85__
    Serial.begin(57600);
#endif
    score_board.begin(0x70);
    for (int i = 1; i <= 12; i++)
    {
        goal[i].get_goal_id(i);
        goal[i].get_button_pin(*(ButtonPin + i));
        goal[i].get_led_pin(*(LedPin + i));
        goal[i].goal_setup();
        
    }
    pinMode(ResetButtonPin, INPUT);
}

void loop()
{
    

    ResetButtonState = digitalRead(ResetButtonPin);
    if (ResetButtonState == HIGH && !game_start)
    {
        game_start = true;

        Serial.println("イエッタイガー");
        for (int i = 1; i <= 12; i++)
            goal[i].button_state = 0;

        time_new_kick_start = millis();
        Serial.println(time_new_kick_start);

        randomSeed(analogRead(0));
        int temp_num[13];
        for (int i = 1; i <= 12; i++)
            temp_num[i] = i;
        
        for (int i = 1; i <= 12; i++)
        {
            int temp_random = random(i, 12);
            temp_change = *(temp_num + i);
            *(temp_num + i) = *(temp_num + temp_random); //随机交换i项和i~11中一项
            *(temp_num + temp_random) = temp_change;
        }
        for (int i = 1; i <= 12; i++)
        {
            random_order[i] = *(temp_num + i);
            
        }


        trial = 1;
        score = 0;
        delay(1000);
    }

    if(game_start){
        
        
        this_turn_goal = *(random_order + trial );
        one_kick_finish = false;
        time_new_kick_start = millis();
        
        for (int loc = 1; loc <= 12; loc++){
            goal[loc].button_state = digitalRead(goal[loc].button_pin);
            
        }

        if(!value_set)
        {
            Serial.print(this_turn_goal);
            Serial.print(" ");
            Serial.println();
            for (int i = 0; i < 9; ++i)
            {
                int x = goal[0].get_x(this_turn_goal) + X_DIR[i];
                int y = goal[0].get_y(this_turn_goal) + Y_DIR[i];
                if (x > 0 && x <= 3 && y > 0 && y <= 4)
                {
                    int l = 4 * (x - 1) + y;
                    goal[l].hit_then_zero = false;
                    goal[l].target_value = SCORE[i];
                    Serial.print(l);
                    Serial.print(" ");
                    Serial.print(SCORE[i]);
                    Serial.print("  ");
                }
            }
            value_set =true;
        }        
       

        // this_game.all_goal_work(random_order[trial]);

        goal[this_turn_goal].led_work(true);
        for (int i = 1; i <= 12; i++)
        {
            goal[i].button_work();
        }

        for (int n = 1; n <= 12; n++)//one_kick_finish 自动变1 lzhshit
        {
            if (goal[n].activated)
            {
                one_kick_finish = true;
                wait_for_button = true;   
            }
        }



        if(wait_for_button){//使得所有按钮被触发
            
            Serial.print("This trial ");
            Serial.print(this_turn_goal);
            Serial.print(" ");
            Serial.println();
            Serial.print("closed ");

            Serial.println();
            for (int n = 1; n <= 12; n++){
                Serial.print(n);
                Serial.print(goal[n].activated);
                Serial.print(" ");
            }
            
            wait_for_button = false;
            goal[this_turn_goal].led_work(false);
            delay(1200);
        }
          
        
        

        for (int i = 1; i <= 12; i++)
        {
            if (goal[i].activated && !goal[i].hit_then_zero)
            {
                part_hit++;
                score = score + goal[i].target_value;
                Serial.println();
                Serial.print("Goal [");
                Serial.print(i);
                Serial.println("] has been hit");
//                Serial.print(part_hit);
//                Serial.print(" ");
//                Serial.println(score);
            }
            
        }

        for (int i = 1; i<=12; i++){
            if (goal[i].activated && goal[i].hit_then_zero)
                score = 0; 
                
        }


        //kick结束算分部分
//        Serial.println(score);

        //end part (score and ready for next)
        

        time_now = millis();
//        Serial.println(time_now - time_new_kick_start);
//        if (time_now - time_new_kick_start > 10000)
//            one_kick_finish = true;
    }
    
   
    
    if (one_kick_finish ) //end part
    {
        value_set =false;
        part_hit = min(part_hit, 3);
        score = score / part_hit;
        if (score == -1)
          score = 0;
        total_score = total_score + score;

        Serial.print("trial");
        Serial.print(" ");
        Serial.print(trial);
        Serial.print(" ");
        Serial.print("part_hit");
        Serial.print(" ");
        Serial.print(part_hit);
        Serial.print(" ");
        Serial.print("score");
        Serial.print(" ");
        Serial.println(score);
        

        

        score_board.print(score,DEC);
        score_board.writeDisplay();
        delay(1250);
        /**********************************/
        trial++;
        score = 0;
        part_hit = 0;

        one_kick_finish = false;
        Serial.println();
        Serial.println();
        Serial.println();
    }
    

    if (trial == 9)
    {
        delay(3000);
        score_board.print(total_score,DEC);
        score_board.writeDisplay();
        game_start = false;
        Serial.println("Game ends");
        delay(3000);
    }
}
