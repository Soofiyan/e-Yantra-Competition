#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

uint8_t ir = 0;
int counter = 0;

void lift_up(void) {
    
    
}

void lift_down(void) {
    
    
}

void motors_up(void) {
    PORTD |= ((1<<4) | (1<<6));
    PORTD &= ~(1<<7);
    PORTD &= ~(1<<5);
}

void motors_down(void){
    PORTD |= ((1<<5) | (1<<7));
    PORTD &= ~(1<<4);
    PORTD &= ~(1<<6);
}

void stop(void){
    PORTD &= 0x0F;
}

void port_init() {
    DDRD |= 0xF0;
    DDRC = 0x00;
    PORTD = 0x00;
}

int main(void) {
    while(1){
        ir = PINC;
        if (((ir & 0x20) != 0x20) && (counter == 0))
        {
            while(!counter)
            {
                motors_up();
                if(PIND & 0x04 == 0x04)
                {
                    counter = 1;
                    stop();
                }
            }
        }
        if (((ir & 0x20) != 0x20) && (counter == 1))
        {
            while((PIND & 0x08) == 0x08)
            {
                motors_down();
            }
            stop();
            counter = 0;
        }
        _delay_ms(2000);
    }
}
