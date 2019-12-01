#include "sonar.h"

void suivreMur(bool mur)
{
   
    while(mur)
    {
        PORTB |=(1<<PB3);
        _delay_us(10);
        PORTB &=~(1<<PB3);
        uint16_t distance=pulse/58;
        uart.transmissionUART(distance);
        _delay_ms(50);
		ajustementPWM (1,1);
		while(distance>15)
		{
			//ajustementPWM (0,0.5);
			tournerUnPeuGauche();
			PORTB |=(1<<PB3);
        	_delay_us(10);
        	PORTB &=~(1<<PB3);
			distance=pulse/58;
            uart.transmissionUART(distance);
			_delay_ms(50);
		}
		while(distance==15)
		{
			//ajustementPWM (0.5,0.5);
			avancerVitesseConst(0.5);
			PORTB |=(1<<PB3);
        	_delay_us(10);
        	PORTB &=~(1<<PB3);
			distance=pulse/58;
            uart.transmissionUART(distance);
			_delay_ms(50);
		}
		while(distance<15)
		{
			//ajustementPWM (0.5,0);
			tournerUnPeuDroite();
			PORTB |=(1<<PB3);
        	_delay_us(10);
        	PORTB &=~(1<<PB3);
			distance=pulse/58;
            uart.transmissionUART(distance);              
			_delay_ms(50);
		}
    }
}

