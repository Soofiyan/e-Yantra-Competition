#define red_min 8000
#define green_min 15000
#define blue_min 13000
#define red_max 17200
#define green_max 24000
#define blue_max 19000

int result1,result2,result3,result_left,result_right,result;
//result1, result2 and result3 are for red, green and blue filter respectively.
uint8_t prev_colour;
uint8_t colour;

/*
*Function Name: rgb_port_config
*Input:None
*Output:None
*Logic:This function initializes the rgb led
*Example call: rgb_port_config().
*/
void rgb_port_config (void)
{
  /*****************************************
  Define DDR and PORT values for the port on which RGB LED is connected
  ******************************************/
  DDRK |= 0x38; //set rgb as output
  PORTK |= 0x38; //make led off
}
/*
*Function Name: buzzer_config
*Input:None
*Output:None
*Logic:This function initializes the buzzer
*Example call: buzzer_config().
*/
void buzzer_config(){
	DDRF |= 0x20;
}
/*
*Function Name: timer5_init
*Input:None
*Output:None
*Logic:This function initializes Timer 5
*Example call: timer5_init().
*/
void timer5_init(void)
{
	TCCR5A = 0x00;
	TCCR5B |= (1<<CS50);
	TCNT5 = 0;
}
/*
*Function Name: timer5_reset
*Input:None
*Output:None
*Logic:This function resets Timer 5
*Example call: timer5_reset().
*/
void timer5_reset(void)
{
	TCCR5A = 0x00;
	TCCR5B = 0x00;
	TCNT5 = 0;
}
/*
*Function Name: tcs_init
*Input:None
*Output:None
*Logic:This function initialise tcs sensor
*Example call: tcs_init().
*/
void tcs_init(void)
{
	DDRB |= 0xF0;//s0 s1 s3 s2
	DDRD &= ~(1<<0);//input pin
	PORTB |= (1<<5);
	PORTB &= ~(1<<4);
}
/*
*Function Name: check_nut
*Input:None
*Output:None
*Logic:This function gets the reading of each nut by comparing its threshold min and max values.
*Example call: check_nut().
*/
void check_nut(void)
{
	for(int i = 0;i<= 2;i++){
	PORTB &= ~((1<<6));
	PORTB &= ~(1<<7);//red
	if(!(PIND & (1<<0)))
	{
		while(!(PIND & (1<<0)));
	}
	while((PIND & (1<<0)));//Wait for falling edge
	timer5_init();
	while(!(PIND & (1<<0)));//Wait for rising edge
	result1 = TCNT5;
	_delay_ms(50);
	timer5_reset();
	timer5_init();
	PORTB |= (1<<6)|(1<<7);//green
	if(!(PIND & (1<<0)))
	{
		while(!(PIND & (1<<0)));
	}
	while((PIND & (1<<0)));//Wait for falling edge
	timer5_init();
	while(!(PIND & (1<<0)));//Wait for rising edge
	result2 = TCNT5;
	_delay_ms(50);
	timer5_reset();
	timer5_init();
	PORTB &= ~((1<<7));
	PORTB |= (1<<6);//blue
	if(!(PIND & (1<<0)))
	{
		while(!(PIND & (1<<0)));
	}
	while((PIND & (1<<0)));//Wait for falling edge
	timer5_init();
	while(!(PIND & (1<<0)));//Wait for rising edge
	result3 = TCNT5;
	_delay_ms(50);
	timer5_reset();
}	
	if(result1 >= red_min && result1 <= red_max)
	{
		PORTK |= 0x38;
		PORTK &= ~(1<<3);
		_delay_ms(500);
		PORTK |= 0x38;
		colour = 1;
		nut_status[nuts_index] = 1;
	}
	else if(result2 >= green_min && result2 <= green_max && result3 >= 16000 && result3 <= 22000)
	{
		PORTK |= 0x38;
		PORTK &= ~(1<<4);
		_delay_ms(500);
		PORTK |= 0x38;
		colour = 2;
		nut_status[nuts_index] = 1;
	}
	else if(result1 >= 21000 && result1 <= 26000 && result2 >= 22500 && result2 <= 28000 && result3 >= blue_min && result3 <= blue_max)
	{
		PORTK |= 0x38;
		PORTK &= ~(1<<5);
		_delay_ms(500);
		PORTK |= 0x38;
		colour = 3;
		nut_status[nuts_index] = 1;
	}
	else
	{
		PORTK |= 0x38;
		colour = 0;
		nut_status[nuts_index] = 0;
	}
}