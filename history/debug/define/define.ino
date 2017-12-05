#include <Goal.h>

Goal goal[12];
int temp_closed[4] = {-1, -1, -1, -1};
int temp_corner[4] = {-1, -1, -1, -1};

void setup() {
  // put your setup code here, to run once:
Serial.begin(57600);

  for (int i = 0; i <= 11; i++)
  {
    goal[i].get_goal_id(i);
    // goal[i].get_button_pin(*(ButtonPin + i));
    // goal[i].get_led_pin(*(LedPin + i));
    // goal[i].goal_setup();
    // pinMode(ResetButtonPin, INPUT);
  }



    for(int this_turn_goal = 0; this_turn_goal <= 11; this_turn_goal ++){
    Serial.print(this_turn_goal);
    Serial.print("-----");
    Serial.print("temp_closed ");
    
    for (int i = 0; i <= 3; i++)
    {
      int j = 0;
      if (goal[this_turn_goal].define_closed_button(i + 1) != 100)
      {
        temp_closed[j] = goal[this_turn_goal].define_closed_button(i + 1);
        j++;
      }
      Serial.print(temp_closed[j]);
      Serial.print("   ");
    }
    Serial.print("temp_corner ");
    Serial.print(" ");
    for (int i = 0; i <= 3; i++)
    {
      int j = 0;
      if (goal[this_turn_goal].define_corner_button(i + 1) != 100)
      {
        temp_corner[j] = goal[this_turn_goal].define_corner_button(i + 1);
        j++;
      }
      Serial.print(temp_corner[j]);
      Serial.print("   ");
    }
    Serial.println("");
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  
}
