/*
*
* Function Name: motion_pin_config
* Input: void
* Output: void
* Logic: Used to configure the ports for motors.
* Example Call: motion_pin_config();
*
*/
//Function to configure ports to enable robot's motion
void motion_pin_config (void)
{
	DDRA = DDRA | 0x55;
	PORTA = PORTA & 0xAA;
	DDRE = DDRE | 0x30;   //Setting PL3 and PL4 pins as output for PWM generation
	PORTE = PORTE | 0x30; //PL3 and PL4 pins are for velocity control using PWM.
}

/*
*
* Function Name: timer3_init
* Input: void
* Output: void
* Logic: Used to initialise timer 3.
* Example Call: timer3_init();
*
*/
// Timer 3 initialized in PWM mode for velocity control
// Prescale:256
// PWM 8bit fast, TOP=0x00FF
// Timer Frequency:225.000Hz
void timer3_init()
{
	TCCR3B = 0x00;	//Stop
	TCNT3H = 0xFF;	//Counter higher 8-bit value to which OCR5xH value is compared with
	TCNT3L = 0x01;	//Counter lower 8-bit value to which OCR5xH value is compared with
	OCR3BH = 0x00;	//Output compare register high value for Left Motor
	OCR3BL = 0xFF;	//Output compare register low value for Left Motor
	OCR3CH = 0x00;	//Output compare register high value for Right Motor
	OCR3CL = 0xFF;	//Output compare register low value for Right Motor
	TCCR3A = 0xA9;	/*{COM3A1=1, COM3A0=0; COM3B1=1, COM3B0=0; COM3C1=1 COM3C0=0}
 					  For Overriding normal port functionality to OCRnA outputs.
				  	  {WGM31=0, WGM30=1} Along With WGM32 in TCCR3B for Selecting FAST PWM 8-bit Mode*/
	
	TCCR3B = 0x0B;	//WGM32=1; CS32=0, CS31=1, CS30=1 (Prescaler=64)
}
/*
*
* Function Name: timer3_init
* Input: velocity to be limited
* Output: unsigned 8 bit limited velocity
* Logic: Used to limit the velocity between 0 to 255 after using pid controller.
* Example Call: timer3_init().
*
*/
uint8_t limit_vel(int vel)
{
	if(vel<=0)
	{
		vel = 0;
	}
	else if(vel>=255)
	{
		vel = 255;
	}
	return vel;
	
}
/*
*
* Function Name: velocity
* Input: velocity for left wheel and velocity for right wheel
* Output: None
* Logic: Used to limit the velocity between 0 to 255 after using pid controller.
* Example Call: velocity(150,150).
*
*/
void velocity(int left_motor, int right_motor) {
	if(left_motor < 0)
	{
		left_motor = -left_motor;
		PORTA |= (1<<4);
		PORTA &= ~(1<<6);
	}
	else if(left_motor >= 0)
	{
		PORTA &= ~(1<<4);
		PORTA |= (1<<6);
	}
	else
	{
		PORTA &= ~(1<<4);
		PORTA &= ~(1<<6);
	}
	if(right_motor >= 0)
	{
		PORTA |= (1<<0);
		PORTA &= ~(1<<2);
	}
	else if(right_motor < 0)
	{
		PORTA &= ~(1<<0);
		PORTA |= (1<<2);
		right_motor = -right_motor;
	}
	else
	{
		PORTA &= ~(1<<0);
		PORTA &= ~(1<<2);
	}
	OCR3BL = left_motor;
	OCR3CL = right_motor;
}

/*
*
* Function Name: forward
* Input: None
* Output: None
* Logic: Used to give a forward push to the bot.
* Example Call: forward().
*
*/
void forward (void)
{
	PORTA = PORTA & 0xAA;
	PORTA |= 0x41;
}
/*
*
* Function Name: right
* Input: None
* Output: None
* Logic: Used to give a right push to the bot.
* Example Call: right().
*
*/
void right (void)
{
	velocity(200,-200);
}
/*
*
* Function Name: left
* Input: None
* Output: None
* Logic: Used to give a left push to the bot.
* Example Call: left().
*
*/
void left (void)
{
	velocity(-250,200);
}
/*
*
* Function Name: stop
* Input: None
* Output: None
* Logic: Used to stop the bot.
* Example Call: stop().
*
*/
void stop (void)
{
	PORTA = PORTA & 0xAA;
}