/*
*
* Function Name: servo1_pin_config
* Input: void
* Output: void
* Logic: Used to initialise servo 1 pins
* Example Call: servo1_pin_config();
*
*/
//Configure PORTB 5 pin for servo motor 1 operation
void servo1_pin_config (void)
{
	DDRH  = DDRH | 0x08;  //making PORTB 5 pin output
	PORTH = PORTH | 0x08; //setting PORTB 5 pin to logic 1
}
/*
*
* Function Name: servo2_pin_config
* Input: void
* Output: void
* Logic: Used to initialise servo 2 pins
* Example Call: servo2_pin_config();
*
*/
//Configure PORTB 6 pin for servo motor 2 operation
void servo2_pin_config (void)
{
	DDRE  = DDRE | 0x08;  //making PORTB 6 pin output
	PORTE = PORTE | 0x08; //setting PORTB 6 pin to logic 1
}
/*
*
* Function Name: servo3_pin_config
* Input: void
* Output: void
* Logic: Used to initialise servo 3 pins
* Example Call: servo3_pin_config();
*
*/
//Configure PORTB 7 pin for servo motor 3 operation
void servo3_pin_config (void)
{
	DDRH  = DDRH | 0x20;  //making PORTB 6 pin output
	PORTH = PORTH | 0x20; //setting PORTB 6 pin to logic 1
}

//TIMER1 initialization in 10 bit fast PWM mode  
//prescale:256
// WGM: 7) PWM 10bit fast, TOP=0x03FF
// actual value: 52.25Hz 
void timer1_init(void)
{
 TCCR4B = 0x00; //stop
 TCNT4H = 0xFC; //Counter high value to which OCR1xH value is to be compared with
 TCNT4L = 0x01;	//Counter low value to which OCR1xH value is to be compared with
 OCR4AH = 0x03;	//Output compare Register high value for servo 1
 OCR4AL = 0xFF;	//Output Compare Register low Value For servo 1
 OCR4CH = 0x03;	//Output compare Register high value for servo 2
 OCR4CL = 0xFF;	//Output Compare Register low Value For servo 2
 ICR4 = 1249;
 TCCR4A = 0xAB; /*{COM1A1=1, COM1A0=0; COM1B1=1, COM1B0=0; COM1C1=1 COM1C0=0}
 					For Overriding normal port functionality to OCRnA outputs.
				  {WGM11=1, WGM10=1} Along With WGM12 in TCCR1B for Selecting FAST PWM Mode*/
 TCCR4C = 0x00;
 TCCR4B = 0x0C; //WGM12=1; CS12=1, CS11=0, CS10=0 (Prescaler=256)
 
 TCCR3B = 0x00; //stop
 TCNT3H = 0xFC; //Counter high value to which OCR1xH value is to be compared with
 TCNT3L = 0x01;	//Counter low value to which OCR1xH value is to be compared with
 OCR3AH = 0x03;	//Output compare Register high value for servo 1
 OCR3AL = 0xFF;	//Output Compare Register low Value For servo 1
 ICR3 = 1249;
 TCCR3A = 0xAB; /*{COM1A1=1, COM1A0=0; COM1B1=1, COM1B0=0; COM1C1=1 COM1C0=0}
 					For Overriding normal port functionality to OCRnA outputs.
				  {WGM11=1, WGM10=1} Along With WGM12 in TCCR1B for Selecting FAST PWM Mode*/
 TCCR3C = 0x00;
 TCCR3B = 0x0C; //WGM12=1; CS12=1, CS11=0, CS10=0 (Prescaler=256)
}

/*
*
* Function Name: servo_1
* Input: void
* Output: void
* Logic: This functions rotate the servo 1 motor at a specific degree.
* Example Call: servo_1(50);
*
*/
//Function to rotate Servo 1 by a specified angle in the multiples of 1.86 degrees
void servo_1(unsigned char degrees)
{
	float PositionServo = 0;
	PositionServo = ((float)degrees / 3) + 15;
	OCR4AH = 0x00;
	OCR4AL = (unsigned char) PositionServo;
	_delay_ms(550);
}
/*
*
* Function Name: servo_2
* Input: void
* Output: void
* Logic: This functions rotate the servo 2 motor at a specific degree.
* Example Call: servo_2(50);
*
*/

//Function to rotate Servo 2 by a specified angle in the multiples of 1.86 degrees
void servo_2(unsigned char degrees)
{
	float PositionServo = 0;
	PositionServo = ((float)degrees / 0.8) +25;
	OCR3A = (unsigned char) PositionServo;
	_delay_ms(450);
}

/*
*
* Function Name: servo_3
* Input: void
* Output: void
* Logic: This functions rotate the servo 3 motor at a specific degree.
* Example Call: servo_3(50);
*
*/
//Function to rotate Servo 3 by a specified angle in the multiples of 1.86 degrees
void servo_3(unsigned char degrees)
{
	float PositionServo = 0;
	PositionServo = ((float)degrees / 3) + 15;
	OCR4CH = 0x00;
	OCR4CL = (unsigned char) PositionServo;
	_delay_ms(550);
}
/*
*
* Function Name: servo_1_free
* Input: void
* Output: void
* Logic: This functions free the servo 1.
* Example Call: servo_1_free();
*
*/
void servo_1_free (void) //makes servo 1 free rotating
{
	OCR4AH = 0x03;
	OCR4AL = 0xFF; //Servo 1 off
}
/*
*
* Function Name: servo_2_free
* Input: void
* Output: void
* Logic: This functions free the servo 2.
* Example Call: servo_2_free();
*
*/
void servo_2_free (void) //makes servo 2 free rotating
{
	OCR3AH = 0x03;
	OCR3AL = 0xFF; //Servo 2 off
}

/*
*
* Function Name: servo_3_free
* Input: void
* Output: void
* Logic: This functions free the servo 3.
* Example Call: servo_3_free();
*
*/
void servo_3_free (void) //makes servo 3 free rotating
{
	OCR4CH = 0x03;
	OCR4CL = 0xFF; //Servo 3 off
}
/*
*
* Function Name: servo_init
* Input: void
* Output: void
* Logic: This functions initialise the servo motors.
* Example Call: servo_init();
*
*/
void servo_init(){
	 servo1_pin_config(); //Configure PORTB 5 pin for servo motor 1 operation
	 servo2_pin_config(); //Configure PORTB 6 pin for servo motor 2 operation
	 servo3_pin_config(); //Configure PORTB 7 pin for servo motor 3 operation
}

/*
*
* Function Name: pickup
* Input: Previous and current nodes
* Output: void
* Logic: This functions takes the previous and current node and sets the angle.
* Example Call: pickup(12,2);
*
*/
void pickup(int node_p,int node_c){
    servo_2(120); 
    if ((node_p == 17 && node_c == 18) || (node_p == 18 && node_c == 19) || (node_p == 20 && node_c == 21) || (node_p == 21 && node_c == 22) || (node_p == 22 && node_c == 23)) 
	   servo_3(10);
    else if ((node_p == 18 && node_c == 17) || (node_p == 19 && node_c == 18) || (node_p == 20 && node_c == 19) || (node_p == 22 && node_c == 21) || (node_p == 23 && node_c == 22)) 
	   servo_3(170);  
    else if ((node_p == 13 && node_c == 17) || (node_p == 16 && node_c == 23)) 
	   servo_3(110);
    else if ((node_p == 14 && node_c == 18) || (node_p == 15 && node_c == 22)) 
	   servo_3(85);  
	else
		servo_3(10);                       
	servo_1(180);
	servo_2(180);
	servo_1(50);
	servo_3(60);
	servo_1_free();
	servo_3_free();
}

/*
*
* Function Name: place_rack
* Input: Position to keep in the rack
* Output: void
* Logic: This functions takes the position to keep the nut in the rack.
* Example Call: place_rack(2);
*
*/
void place_rack(int position){
	switch(position){
		case 1: servo_3(48);
				servo_1(2);
				break;
		case 2: servo_3(85);
				servo_1(3);
				break;
		case 3: servo_3(124);
				servo_1(2);
				break;
		default:break; 		
	}
	servo_2(150);
	servo_1(50);
	servo_3(115);
	servo_1_free();
	servo_3_free();
	servo_2_free();
}

/*
*
* Function Name: pick_rack
* Input: Position of the rack
* Output: void
* Logic: This functions takes the position to pick the nut from the rack.
* Example Call: place_rack(2);
*
*/
void pick_rack(int position){
	servo_1(50);
	servo_2(150);
	switch(position){
		case 1: servo_3(45);
		servo_1(5);
		break;
		case 2: servo_3(83);
		servo_1(8);
		break;
		case 3: servo_3(124);
		servo_1(5);
		break;
		default:break;
	}
	servo_2(180);
	servo_1(50);
	servo_1_free();
	servo_3_free();
	rack[position] = 0;
}

/*
*
* Function Name: place
* Input: Position of the rack
* Output: void
* Logic: This functions takes the previous and current node and sets the angle to place the nut.
* Example Call: place(2,12);
*
*/
void place(int node_p,int node_c){
	 if ((node_p == 2 && node_c == 9) || (node_p == 11 && node_c == 10)){ 
		servo_3(6);
		servo_1(186);
	 }		
	 else if ((node_p == 8 && node_c == 9) || (node_p == 6 && node_c == 10)){
		servo_3(175);
		servo_1(190);
	 }		
	 else if(node_p == 11 && node_c == 12){
		servo_3(92);
		servo_1(180);
	 }	
	 else if((node_p == 8 && node_c == 7) || (node_p == 38 && node_c == 39) || (node_p == 38 && node_c == 37)){
		 servo_3(85);
		 servo_1(180);
	}
	servo_2(150);
	 servo_2(120);
     servo_1(30);
	servo_3(90);
	servo_1_free();
	servo_3_free();
	servo_2_free();
}