/*
 **
 Team Id: eYRC#963
 * Author List: Sorabh,Soofiyan,Shreyas,Pranav
 * Filename: lift.c
 * Theme: Nutty Squirrel
 * Functions: motors_up,motors_down,stop,port_init,timer1_init,velocity
 * Global Variables:
 *
 */

#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

/*
 *
 * Function Name: motors_up
 * Input: void
 * Output: void
 * Logic: Used to move the lift up
 * Example Call: motors_up(); //moves the lift up
 *
 */
void motors_up(void) {
    PORTD |= ((1<<4) | (1<<7));
    PORTD &= ~(1<<6);
    PORTD &= ~(1<<5);
}

/*
 *
 * Function Name: motors_down
 * Input: void
 * Output: void
 * Logic: Used to move the lift down
 * Example Call: motors_up(); //moves the lift down
 *
 */
void motors_down(void){
    PORTD |= ((1<<5) | (1<<6));
    PORTD &= ~(1<<4);
    PORTD &= ~(1<<7);
}

/*
 *
 * Function Name: stop
 * Input: void
 * Output: void
 * Logic: Used to stop the lift
 * Example Call: stop(); //stops the lift
 *
 */
void stop(void){
    PORTD &= 0x0F;
}

/*
 *
 * Function Name: port_init
 * Input: void
 * Output: void
 * Logic: Used to initialize the direction and pwm pins for lift
 * Example Call: port_init(); //initialize the pins for motors of lift
 *
 */
void port_init() {
    DDRD |= 0xF0; //direction pins of motor on D7,D6,D5,D4, So set output
    DDRD &= 0xF3; //limit switches on D3,D2. So set as input
    DDRB |= 0x06; //pwm pins on B1,B2 so set as output.
    PORTB |= 0x06;
    DDRC &= ~(1<<5); //IR sensor on PC5. so set as input
    PORTD = 0x00;
}

/*
 *
 * Function Name: timer1_init
 * Input: void
 * Output: void
 * Logic: Used to initialize timer for pwm generation
 * Example Call: timer1_init(); //initialize the timer
 *
 */
void timer1_init()
{
    TCCR1B = 0x00;
    TCNT1H = 0xFF;
    TCNT1L = 0x01;
    OCR1BH = 0x00;
    OCR1BL = 0xFF;
    OCR1AH = 0x00;
    OCR1AL = 0xFF;
    TCCR1A = 0xA9;
    TCCR1B = 0x0B;
}

/*
 *
 * Function Name: velocity
 * Input: unsigned char,unsigned char
 * Output: void
 * Logic: Used to set the velocity for lift
 * Example Call: velocity(100,100); //sets the velocity for lift
 *
 */
void velocity (unsigned char left_motor, unsigned char right_motor)
{
    OCR1BL = (unsigned char)left_motor;
    OCR1AL = (unsigned char)right_motor;
}

int main(void) {
    uint8_t ir,up,down = 0;
    int counter = 0;
    port_init(); //initialize the port
    stop(); //initially stop the lift
    timer1_init(); //initialize timer
    velocity(0,0);
    

    while(1){
        ir = PINC; //read the PORTC value to check IR status
        

        if (!(ir & 0x20) && (counter == 0)) //check if IR reading is HIGH and counter to indicate the position of lift
        {
            up = PIND; //read the PORTD value to check status of limit switch on top position
            while(!(up & 0x04)){ //move the lift up until lift presses the top limit switch
                motors_up();
                velocity(255,255);
                up = PIND;
            }
            while(!(ir & 0x20))
            {
                ir = PINC;
                velocity(80,80); //stop the lift
            }
            _delay_ms(2000);
            velocity(0,0);
            stop();
            counter = 1; //set counter=1 to indicate top position
        }
        

        else if (!(ir & 0x20) && (counter == 1)) //check if IR reading is HIGH and counter to indicate the position of lift
        {
            _delay_ms(1000); //wait for bot to stabilize
            down = PIND; //read the PORTD value to check status of limit switch on bottom position
            while (!(down & 0x08)){ //move the lift down until lift presses the bottom limit switch
                motors_down();
                velocity(255,255);
                down = PIND;
            }
            velocity(0,0);
            _delay_ms(3000); //wait for the bot to move out
            counter = 0; //set counter=0 to indicate bottom position
        }
    }
}
