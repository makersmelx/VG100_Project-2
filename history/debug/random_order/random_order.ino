int temp_change;
int random_order[12];

void setup() {
  // put your setup code here, to run once:
Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int temp_num[12];
  for (int i = 0; i <= 11; i++)
    temp_num[i] = i + 1;
  for (int i = 0; i <= 11; i++)
  {
    int temp_random = random(i,11);
    temp_change = *(temp_num + i);
    *(temp_num + i) = *(temp_num + temp_random); //随机交换i项和i~11中一项
    *(temp_num + temp_random) = temp_change;
  }

  for (int i = 0; i < 7; i++)
  {
    random_order[i] = *(temp_num + i);
    Serial.print(random_order[i]); //11/24一直输入重复的数字
    Serial.print("  ");
  }
  Serial.println("");
  delay(750);
}
