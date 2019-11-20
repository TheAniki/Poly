#include "PWMDEL.h"
#include "PWM_roue.h"
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
const uint16_t a=0;
const uint16_t b=16667; // comme au tp3


int main()
{                   
    DDRA = 0xff; // PORT A est en mode sortie
    DDRB = 0xff; // PORT B est en mode sortie
    DDRC = 0xff; // PORT C est en mode sortie
    DDRD = 0xff; // PORT D est en mode sortie
    PORTB=0X00; 
    for(;;)
    {
       boucle60hz(a,b);
    }
}
