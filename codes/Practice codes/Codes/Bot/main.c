#define F_CPU 16000000UL
#define thresh 150
#define base_pwm 220
#define kp 250
#define ki 0.5
#define kd 250
//150 1.67 180
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#include "lcd.h"
#include <math.h> //included to support power function

uint16_t ADC_Conversion(uint8_t);
void line_follow(void);

int sens[3] = {0, 0, 0};
float sens_count = 0, sens_black = 0;
float vel_l = 0, vel_r = 0;
float error, error_last;
int P, I, D;
int node,node_detect;
int sharp_ir;
bool checknode = 0,checklift = 0;

uint16_t lefts, centres, rights;

//Function to configure LCD port
void lcd_port_config(void) {
    DDRC = DDRC | 0xF0; //all the LCD pin's direction set as output
    DDRA |= 0xA8;
    PORTC = PORTC & 0x0F; // all the LCD pins are set to logic 0 except PORTC 7
    PORTA &= 0x57;
}

//ADC pin configuration
void adc_pin_config(void) {
    DDRF = 0x00;  //set PORTF direction as input
    PORTF = 0x00; //set PORTF pins floating
    DDRK = 0x00;  //set PORTK direction as input
    PORTK = 0x00; //set PORTK pins floating
}

//Function to configure ports to enable robot's motion
void motion_pin_config(void) {
    DDRA = DDRA | 0x55;
    PORTA &= ~((1 << 0) & (1 << 2) & (1 << 4) & (1 << 6));
    DDRE = DDRE | 0x30;   //Setting PL3 and PL4 pins as output for PWM generation
    PORTE = PORTE | 0x30; //PL3 and PL4 pins are for velocity control using PWM.
}

void rgb_init()
{
    DDRK = 0xFF;
    PORTK = 0xFF;
}
//Function to Initialize PORTS
void port_init(void) {
    lcd_port_config();
    adc_pin_config();
    motion_pin_config();
}

// Timer 5 initialized in PWM mode for velocity control
// Prescale:256
// PWM 8bit fast, TOP=0x00FF
// Timer Frequency:225.000Hz
void timer3_init(void) {
    TCCR3B = 0x00; //Stop
    TCNT3H = 0xFF; //Counter higher 8-bit value to which OCR5xH value is compared with
    TCNT3L = 0x01; //Counter lower 8-bit value to which OCR5xH value is compared with
    OCR3BH = 0x00; //Output compare register high value for Left Motor
    OCR3BL = 0xFF; //Output compare register low value for Left Motor
    OCR3CH = 0x00; //Output compare register high value for Right Motor
    OCR3CL = 0xFF; //Output compare register low value for Right Motor
    TCCR3A = 0xA9; /*{COM3A1=1, COM3A0=0; COM3B1=1, COM3B0=0; COM3C1=1 COM3C0=0}
                    For Overriding normal port functionality to OCRnA outputs.
                    {WGM31=0, WGM30=1} Along With WGM32 in TCCR3B for Selecting FAST PWM 8-bit Mode*/
    TCCR3B = 0x0B; //WGM32=1; CS32=0, CS31=1, CS30=1 (Prescaler=64)
}

//Function to Initialize ADC
void adc_init(void) {
    ADMUX = (0 << REFS1) | (1 << REFS0) | (0 << ADLAR);                                             // AVcc //  right adjusted
    ADCSRA = (1 << ADEN) | (0 << ADATE) | (0 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // bit4 ADC EOC flag // prescalar- 111 - 128 division factor
    ADCSRB = 0x00;
}

int limit_vel(int velocity) {
    if (velocity >= 255) {
        return 255;
    } else if (velocity <= -255) {
        return -255;
    } else {
        return velocity;
    }
}
//This Function accepts the Channel Number and returns the corresponding Analog Value
uint16_t ADC_Conversion(uint8_t ch) {
    ADMUX = ADMUX & 0b11100000;   //Clearing all the mux
    ADCSRB = ADCSRB & 0b11110111; //------"-"-----------
    ch = ch & 0b00001111;
    if (ch <= 7) {
        ch = ch & 0b00000111; //
        ADMUX = ADMUX | ch;
        ADCSRB = 0x00;
    } else {
        ch = ch - 8;
        ch = ch & 0b00000111;
        ADMUX = ADMUX | ch;
        ADCSRB = 0x00;
        ADCSRB = ADCSRB | (1 << MUX5);
    }
    ADCSRA = ADCSRA | (1 << ADSC); //Bit 6 to start conversion-ADSC
    while (!(ADCSRA & (1 << ADIF)))
        ; // Wait for conversion to complete
    return (ADC);
}

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
    OCR3CL = right_motor-5;
}

void forward(void) {
    PORTA = PORTA & 0xAA;
    PORTA |= 0x41;
}

void stop(void) {
    PORTA = 0xAA;
}
void uturn()
{
    velocity(100,-80);
    _delay_ms(800);
    centres = ADC_Conversion(2);
    while(centres <= 250)
    {
        centres = ADC_Conversion(2);
    }
    stop();
    _delay_ms(500);
    node_detect = 0;
    checknode = 1;
}
void progress_task()
{
    if(checknode == 0)
    {
        if(sharp_ir >=430 && checklift == 0)
        {
            stop();
            _delay_ms(3500);
            checklift = 1;
        }
        else if(sharp_ir >= 550 && checklift == 1)
        {
            uturn();
        }
    }
    else
    {
        if(node_detect == 2)
        {
            stop();
            _delay_ms(5000);
            node_detect++;
        }
        else if(node_detect == 5)
        {
            stop();
            PORTK = ~(1<<3);
            _delay_ms(100000);
        }
    }
}
void init_devices(void) {
    cli(); //Clears the global interrupts
    port_init();
    adc_init();
    timer3_init();
    sei(); //Enables the global interrupts
}

void line_follow(void) {
    int i = 0;
    sens_count = 0;
    sens_black = 0;
    for (i = 0; i <= 2; i++) {
        sens[i] = ADC_Conversion(i + 1);
        if (sens[i] > thresh) //on white line
        {
            sens_black += i + 1;
            sens_count++;
        }
    }
    error = (sens_black / sens_count) - 2;
    lefts = ADC_Conversion(1);
    centres = ADC_Conversion(2);
    rights = ADC_Conversion(3);
    if(lefts > thresh && centres > thresh && rights <= thresh)
    {
        //        error = error_last;
        node++;
    }
    else if(lefts <= thresh && centres > thresh && rights > thresh)
    {
        //        error = error_last;
        node++;
    }
    else if(lefts > thresh && centres > thresh && rights > thresh)
    {
        //        error = error_last;
        node++;
    }
    else if(lefts < thresh && centres < thresh && rights < thresh)
    {
        error = error_last;
    }
    else if(rights > 250 || lefts > 250 || centres > 440)
    {
        node++;
    }
    else
    {
        if(node >= 1)
        {
            node_detect ++;
            node = 0;
            //            forward();
            //            OCR3BL = 150;
            //            OCR3CL = 150;
            //            _delay_ms(10);
            //            stop();
            //            _delay_ms(100);
        }
    }
    
    
    P = (int)error * kp;
    I += error * ki;
    D = (int)((error - error_last) * kd);
    vel_l = limit_vel(base_pwm + P + I + D);
    vel_r = limit_vel(base_pwm - P - I - D);
    error_last = error;
    velocity(vel_l, vel_r);
    progress_task();
    
}

//void line_follow(void) {
//    int i = 0;
//    lefts = ADC_Conversion(1);
//    centers = ADC_Conversion(2);yy
//    rights = ADC_Conversion(3);
//    if(lefts <= thresh && centres > thresh && rights <= thresh)
//    {
//        error = 0;
//    }
//    else if(lefts > thresh && centres <= thresh && rights <= thresh)
//    {
//        error = 2;
//    }
//    else if(lefts <= thresh && centres <= thresh && rights > thresh)
//    {
//        error = -2;
//    }
//    else if(lefts > thresh && centres > thresh && rights <= thresh)
//    {
//        error = 1;
//    }
//    else if(lefts <= thresh && centres > thresh && rights > thresh)
//    {
//        error = -1;
//    }
//    else if(lefts <= thresh && centres <= thresh && rights <= thresh)
//    {
//        stop();
//    }
//    else
//    {
//        error = 0;
//    }
//    P = (error*kp);
//    I += error*ki;
//    vel_l = base_pwm + P;
//    vel_r = base_pwm - P;
//    velocity(vel_l,vel_r);
//}

int main(void) {
    init_devices();
    rgb_init();
//       lcd_set_4bit();
//        lcd_init();
    _delay_ms(2000);
    while (1) {
                sharp_ir = ADC_Conversion(0);
//        lefts = ADC_Conversion(1);
//        centres = ADC_Conversion(2);
//        rights = ADC_Conversion(3);
        //        {
        //            line_follow();
        //        }
        //        else
        //        {
        //            stop();
        //        }
        //forward();
        
        
        //line_follow();
        velocity(255,255);
        /*if(node_detect == 1)
         {
         PORTK = ~(1<<3);
         }
         else if(node_detect == 2)
         {
         PORTK = ~(1<<4);
         }
         else if(node_detect == 3)
         {
         PORTK = ~(1<<5);
         node_detect = 0;
         }*/
//         lcd_print(1, 1, lefts, 4);
//        lcd_print(1,11, rights, 4);
//        lcd_print(1, 6, centres, 4);
        //lcd_print(2,1,sharp_ir,5);
    }
}
