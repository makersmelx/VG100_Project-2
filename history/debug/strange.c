#include <stdio.h>
#include <windows.h>
#include <math.h>



int define_corner_button(int goal_id ,int loc) //1 for up-left; 2 for up-right ; 3 for down-left ; 4 for down-right
{
    int prevent_invalid(int number)
    {
       
        
        if (7 < number && number < 12 || 13 < number && number < 18 || 19 < number && number < 24)
        {
            
        }
        else
        {
            number = 100;
        }

        return number;
    }

    int goal_num = goal_id;
    int delta = 7 + 2*(int)((goal_num ) / 4.5) ;
    goal_num = goal_num + delta;

    switch (loc)
    {
    case 1:
        goal_num = prevent_invalid(goal_num - 7);
        break;
    case 2:
        goal_num = prevent_invalid(goal_num - 5);
        break;
    case 3:
        goal_num = prevent_invalid(goal_num + 5);
        break;
    case 4:
        goal_num = prevent_invalid(goal_num + 7);
        break;
    }

    if(goal_num != 100)
        goal_num = goal_num - 2*(int)(goal_num/12)- 7  ;
    if(goal_num  != 100 && goal_num > 6)
        goal_num = goal_num -2*(int)(goal_num / 9) ;
    return goal_num;
}

int main(){
    
    for (int i = 0; i <=11; i++){

        for (int j =1; j<= 4; j++){
            printf("%-5d",define_corner_button(i+1,j));
        }
        printf("\n");
    }

    system("pause");

}