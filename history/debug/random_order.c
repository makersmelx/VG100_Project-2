#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include<windows.h>


int num = 12;
int take = 8;
void swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int random(int min,int max)
{
    srand(time(NULL));
    int temp;
    temp = rand() % (max-min + 1)+min;
    return temp;
}
int main(){
    int temp_num[12];
    int output[8]; 
    for (int i = 1; i <= num; i++)
        temp_num[i-1] = i;
    for (int i = 0; i <= num - 1; i++)
        swap((temp_num+i), temp_num + random(i, num - 1));
    for (int i = 0; i < take; i++)
    {
        output[i] = *(temp_num + i );
        printf("%d\n", output[i]);
    }

    system("pause");
}