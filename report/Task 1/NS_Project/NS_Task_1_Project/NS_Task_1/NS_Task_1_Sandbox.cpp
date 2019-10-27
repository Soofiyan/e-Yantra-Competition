#include "NS_Task_1_Sandbox.h"

/*
*
* Function Name: forward_wls
* Input: node
* Output: void
* Logic: Uses white line sensors to go forward by the number of nodes specified
* Example Call: forward_wls(2); //Goes forward by two nodes
*
*/
#define kp 10
#define ki 1
#define kd 10

int sens[3] = {0,0,0};
uint8_t sens_count = 0,sens_white = 0;
uint8_t vel_l = 0,vel_r = 0;
uint8_t node;
int8_t error,error_last;

void forward_wls(unsigned char node)
{
    line_follow();
    forward();
    velocity(vel_l,vel_r);
}
/*
*
* Function Name: left_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn left until black line is encountered
* Example Call: left_turn_wls(); //Turns right until black line is encountered
*
*/
void left_turn_wls(void)
{
    left();
    velocity(200,200);
}

/*
*
* Function Name: right_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn right until black line is encountered
* Example Call: right_turn_wls(); //Turns right until black line is encountered
*/
void right_turn_wls(void)
{
    right();
    velocity(200,200);
}

/*
*
* Function Name: Square
* Input: void
* Output: void
* Logic: Use this function to make the robot trace a square path on the arena
* Example Call: Square();
*/
void Square(void)
{
    velocity(255,100);
    forward();
    _delay_ms(100);
    left();
    _delay_ms(100);
    left();
    _delay_ms(100);
}

void line_follow()
{
    int i = 0;
    sens_count = 0;
    sens_white = 0;
    for(i = 0;i<=2;i++)
    {
        sens[i] = ADC_conversion(i);
        if(sens[i] < 200)         //on white line
        {
           sens_white += i+1;
           sens_count ++; 
        }
    }
    error = (sens_white/sens_count) - 2;
    P = error*kp;
    I = error*ki;
    //D = (error - error_last)*kd;
    vel_l = limit_vel(200 + P + I);
    vel_r = limit_vel(200 - P - I);
    error_last = error;
}

/*
*
* Function Name: Task_1_1
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.1 logic
* Example Call: Task_1_1();
*/
void Task_1_1(void)
{
    
}

/*
*
* Function Name: Task_1_2
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.2 logic
* Example Call: Task_1_2();
*/
void Task_1_2(void)
{
    if(ADC_conversion(1) > 200 && ADC_conversion(2) > 200 && ADC_conversion(3) > 200)
    {
        node++;
        _delay_ms(150);
    }
    switch(node)
    {
        case 0: forward_wls();
                break;
        case 1: right_turn_wls();
                _delay_ms(250);
                node++;
                break;
        case 2: forward_wls();
                break;
        case 3: leftt_turn_wls();
                _delay_ms(250);
                node++;
                break;
        case 4: forward_wls();
                break;
        case 5: left_turn_wls();
                _delay_ms(250);
                node++;
                break;
        case 6: forward_wls();
                break;
        case 7: leftt_turn_wls();
                _delay_ms(250);
                node++;
                break;
        case 8: forward_wls();
                break;
        case 9: right_turn_wls();
                _delay_ms(350);
                node++;
                break;
        case 10: forward_wls();
                break;
        case 11: right_turn_wls();
                _delay_ms(50);
                node++;
                break;
        case 12: forward_wls();
                break;
        case 13: right_turn_wls();
                _delay_ms(50);
                node++;
                break;
        case 14: forward_wls();
                break;
        case 15: right_turn_wls();
                _delay_ms(250);
                node++;
                break;
        case 16: forward_wls();
                break;
        case 17: right_turn_wls();
                _delay_ms(350);
                node++;
                break;
        case 18: forward_wls();
                break;
        case 19: left_turn_wls();
                _delay_ms(250);
                node++;
                break;
        case 20: forward_wls();
                break;
        case 21: leftt_turn_wls();
                _delay_ms(250);
                node++;
                break;
        case 22: forward_wls();
                break;
        case 23: right_turn_wls();
                _delay_ms(250);
                node++;
                break;
        case 24: forward_wls();
                 _delay_ms(800);
                 stop();
                 break;
                
    }
}
uint8_t limit_vel(int velocity)
{
    if(velocity > 255)
    {  
        return 255;
    }
    else if(velocity < 0)
    {
        return 0;
    }
    else
    {
        return velocity;
    }
}