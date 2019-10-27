/*
 * Team Id:963
 * Author list : Sorabh Rathod , Soofiyan Atar
 * File Name : NS_963_task_4_bot.c
 * Created: 1/15/2019 9:23:55 PM 
 * Theme : Nutty Squirrel 
 * Functions : line_follow(),port_init(),init_devices (void),obstacle_found(),obstacle_check()
 * Global Variables : static uint8_t direction[41][41],static uint8_t graph[41][41],static int nodes,int sens[3],int sens_count,int sens_black,
 *					  int vel_l,int vel_r,float error,float error_last,float P,float I,float D,int node_timer,int pickup_zone[6],
 *					  int pickup_zone_index ,int deposit_zone[6] ,int deposit_zone_index, bool done = 0,bool deposits,bool total_done,bool all_nuts_picked,int final_destination,int counters,int total_nuts,int *p,int prev_node,int current_node,int traversed,
 *					  int destination,uint16_t lefts,uint16_t centers,uint16_t rights,uint16_tobstacle,int nuts[6],int nuts_index,bool nut_status[6],bool rack[4],
 *					  #define threshold 200,#define threshold_node 500,#define node_timers 200,int base_pwm,float kp,float ki,float kd.
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

//GLobal variables here
static uint8_t direction[41][41] = {0};
static uint8_t graph[41][41] = {0};
static int nodes = 41;
int sens[3] = {0, 0, 0};
int sens_count = 0, sens_black = 0;
int vel_l = 0, vel_r = 0;
float error, error_last;
float P, I, D;
int node_timer = 0;

int pickup_zone[6] = {17,18,19,21,22,23};
int pickup_zone_index = 0;
int deposit_zone[6] = {9,7,10,12,37,39};
int deposit_zone_index = 0;

bool done = 0;
bool deposits = 0;
bool total_done = 0;
bool all_nuts_picked = 0;
int final_destination;
int counters = 0;
int total_nuts = 6;
int *p;
int prev_node = 34;
int current_node = 34;
int traversed = 2;
int destination;
uint16_t lefts, centers, rights,obstacle = 0;

int nuts[6] = {0};
int nuts_index = 0;
bool nut_status[6] = {0};
bool rack[4] = {0};

#define threshold 200
#define threshold_node 500
#define node_timers 200
int base_pwm  = 220;
float kp = 250;
float ki = 0;
float kd = 250;

#include <math.h> //included to support power function
#include "adc.h"
#include "motor.h"
#include "color_sensor.h"
#include "graph.h"
#include "dijakstra.h" 
#include "servo.h"
#include "color_scanning.h"
#include "deposit_1.h"
#include "deposit_2.h"

//int robotposition(void);
void line_follow(void);

/*
*Function Name : port_init
*Input : None
*Output : None
*Logic : This function will configure  adc, motors, rgb led, buzzer, tcs and servo.
*Example Call: port_init()
*/
//Function to Initialize PORTS
void port_init()
{
	adc_pin_config();
	motion_pin_config();
	rgb_port_config();
	buzzer_config();
	tcs_init();
	servo_init();
}

/*
*Function Name : init_devices
*Input : None
*Output : None
*Logic : This function will initialise adc, timer1, timer3and all the graphs.
*Example Call: init_devices()
*/
void init_devices (void)
{
	cli(); //Clears the global interrupts
	port_init();
	adc_init();
	timer1_init();
	timer3_init();
	velocity(0,0);
	graphs();
	sei(); //Enables the global interrupts
}

/*
*Function Name : line_follow
*Input : None
*Output : None
*Logic : This function will traverse the bot along the line with help of pid controller.
*Example Call: line_follow()
*/
void line_follow(void) {
	int i = 0;
	sens_count = 0;
	sens_black = 0;
	for (i = 0; i <= 2; i++) {
		sens[i] = ADC_Conversion(i + 1);
		if (sens[i] > threshold) //on white line
		{
			sens_black += i + 1;
			sens_count++;
		}
	}
	error = (sens_black / sens_count) - 2;
	lefts = sens[0];
	centers = sens[1];
	rights = sens[2];
	if(lefts > threshold && centers > threshold && rights <= threshold && node_timer >= node_timers)
	{
		stop();
			if (done == 0)
				node_found_color();
			else if(deposits == 0)
				node_found_deposit_1();
			else if (all_nuts_picked == 0)
				node_found_color_2();
			else
				node_found_deposit_2();
			
	}
	else if(lefts <= threshold && centers > threshold && rights > threshold && node_timer >= node_timers)
	{
		stop();
		if (done == 0)
			node_found_color();
		else if(deposits == 0)
			node_found_deposit_1();
		else if (all_nuts_picked == 0)
			node_found_color_2();
		else
			node_found_deposit_2();
	}
	else if(lefts > threshold && centers > threshold && rights > threshold && node_timer >= node_timers)
	{
		stop();
			if (done == 0)
				node_found_color();
			else if(deposits == 0)
				node_found_deposit_1();
			else if (all_nuts_picked == 0)
				node_found_color_2();
			else
				node_found_deposit_2();
	}
	else if((lefts >= threshold_node || centers >= threshold_node || rights >= threshold_node) && node_timer >= node_timers)
	{
		stop();
			if (done == 0)
				node_found_color();
			else if(deposits == 0)
				node_found_deposit_1();
			else if (all_nuts_picked == 0)
				node_found_color_2();
			else
				node_found_deposit_2();
	}
	if(lefts < threshold && centers < threshold && rights < threshold)
	{
		error = error_last;
	}
	P = error * kp;
	I += error * ki;
	D = (error - error_last)*kd;
	int speed = P+I+D;
	vel_l = (base_pwm + speed);
	vel_r = (base_pwm - speed) - 5;
	error_last = error;
	velocity(vel_l, vel_r);
	node_timer++;
}

/*
*Function Name : obstacle_found
*Input : None
*Output : None
*Logic : This function will check that obstacle is present or not and traverse the next path.
*Example Call: obstacle_found()
*/
void obstacle_found(){
	stop();
	if (counters != 1)
	{
		turn(9-counters);
	}
	graph[current_node][destination] = 99;
	graph[destination][current_node] = 99;
	traversed = 2;
	p = dijsktra1(current_node,final_destination);
	destination = *(p + traversed);
	counters = directions(prev_node,current_node,destination); //determine turn number
	turn(counters); //carry out the turn
	stop();
}

/*
*Function Name : obstacle_check
*Input : None
*Output : None
*Logic : This function will check that obstacle is present or not.
*Example Call: obstacle_check()
*/
int obstacle_check(){
	static flag = 0;
	for (int i = 0;i<=3;i++)
	{
		stop();
		if (ADC_Conversion(0) >= 400 && ADC_Conversion(0) <=700)
		{
			flag = 1;
		}
		else{
			flag = 0;
		}
	}
	return flag;
}

/*
*Function Name : main
*Input : None
*Output : returning 0
*Logic : This function is the main function.
*Example Call: main()
*/
int main(void)
{
    init_devices();
	
	servo_1(50);
	servo_3(115);
	servo_2(120);
	servo_1_free();
	servo_3_free();
	servo_2_free();
	stop();
    color_scan();
	deposit_1();
	deposit_2();
	stop();
	while(1){
		PORTF |= 0x20;
	}
}
