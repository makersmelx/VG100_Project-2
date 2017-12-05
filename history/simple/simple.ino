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
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Game.h>
//#include <time.h>//BUG1

int ButtonPin[13] = {0,40, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 42};
int LedPin[13] = {0,41, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int ResetButtonPin = 45;
int ResetButtonState = 0;


int random_order[9];
int temp_change = 0;

unsigned long time_new_kick_start = 0;
unsigned long time_now = 0;

int this_turn_goal = 0;
int part_hit = 0;
int score = 0;
int total_score = 0;

int trial =1;


bool one_kick_finish = false;
bool game_start = false;
bool wait_for_button = false;


Goal goal[13];
Football this_game;
Adafruit_7segment score_board;

void setup()
{
#ifndef __AVR_ATtiny85__
    Serial.begin(57600);
#endif
    //score_board.begin(0x70);
    for (int i = 1; i <= 12; i++)
    {
        goal[i].set_button_pin(ButtonPin[i]);
        goal[i].set_led_pin(LedPin[i]);
        this_game.setup_goal(ButtonPin[i],LedPin[i]);
        
    }
    this_game.set_default();
    pinMode(ResetButtonPin, INPUT);
}

void loop()
{
    ResetButtonState = digitalRead(ResetButtonPin);

    if (ResetButtonState == HIGH && !game_start)
    {
        game_start = true;
        Serial.println("イエッタイガー");
        

        time_new_kick_start = millis();

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
        for (int i = 1; i < 12; i++)
        {
            random_order[i] = *(temp_num + i);
            
        }
        delay(1000);
    }

    if(game_start){
        this_turn_goal = *(random_order + trial );
        one_kick_finish = false;

        time_new_kick_start = millis();

        for (int i = 1; i <= 12; i++)
            goal[i].button_state = digitalRead(goal[i].button_pin);

        this_game.goal_work(trial);
    
        for (int n = 2; n <= 12; n++)//one_kick_finish 自动变1 lzhshit
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
            Serial.println(" ");
            Serial.println();
            for (int n = 2; n <= 12; n++){
                Serial.print(n);
                Serial.print(goal[n].activated);
                Serial.print(" ");
            }
            Serial.println();
            wait_for_button = false;
            goal[this_turn_goal].led_work(false);
            delay(500);
        }

        
        

        for (int i = 2; i <= 12; i++)
        {
            if (goal[i].activated && !goal[i].hit_then_zero)
            {
                part_hit++;
                score = score + goal[i].score;
                Serial.print(part_hit);
                Serial.print(" ");
                Serial.println(score);
            }
              
        }

        for (int i = 2; i <= 12; i++){
            if (goal[i].activated && goal[i].hit_then_zero)
                Serial.println("Zero");
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
        
        part_hit = min(part_hit, 3);
        score = score / part_hit;
        total_score = total_score + score;

        Serial.print("trial");
        Serial.print(trial);
        Serial.print(" ");
        Serial.print("part_hit");
        Serial.print(part_hit);
        Serial.print(" ");
        Serial.print("score");
        Serial.println(score);
        

        

//        score_board.print(score);
//        score_board.writeDisplay();
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
    

    if (trial == 9 && game_start)
    {
        delay(3000);
        score_board.print(total_score);
        score_board.writeDisplay();
        game_start = false;
        Serial.println("Game ends");
        delay(3000);
    }
}
