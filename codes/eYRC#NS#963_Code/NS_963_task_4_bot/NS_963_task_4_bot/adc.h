
void adc_pin_config (void);
void adc_init();
uint16_t ADC_Conversion(uint8_t ch);

//ADC pin configuration
void adc_pin_config (void)
{
	DDRF = 0x00; //set PORTF direction as input
	PORTF = 0x00; //set PORTF pins floating
	DDRK = 0x00; //set PORTK direction as input
	PORTK = 0x00; //set PORTK pins floating
}

//Function to Initialize ADC
void adc_init()
{
	ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<ADLAR);  // AVcc //  right adjusted
	ADCSRA = (1<<ADEN)|(0<<ADATE)|(0<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // bit4 ADC EOC flag // prescalar- 111 - 128 division factor
	ADCSRB = 0x00;
}

//This Function accepts the Channel Number and returns the corresponding Analog Value
uint16_t ADC_Conversion(uint8_t ch)
{
	ADMUX = ADMUX & 0b11100000;    //Clearing all the mux
	ADCSRB = ADCSRB & 0b11110111;  //------"-"-----------
	ch = ch & 0b00001111;
	if ( ch <= 7 )
	{
		ch = ch & 0b00000111; //
		ADMUX = ADMUX | ch;
		ADCSRB=0x00;
	}
	else
	{
		ch = ch-8;
		ch = ch & 0b00000111;
		ADMUX = ADMUX | ch;
		ADCSRB=0x00;
		ADCSRB = ADCSRB | (1<<MUX5);
	}
	ADCSRA = ADCSRA | (1<<ADSC);    //Bit 6 to start conversion-ADSC
	while( !(ADCSRA & (1<<ADIF)) ); // Wait for conversion to complete
	return(ADC);
}
