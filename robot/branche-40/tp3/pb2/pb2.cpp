/*
Auteurs : Ouassim Ouali et Kevin Wassef
*/

#include <avr/io.h> 
#define F_CPU 1000000
#include <util/delay.h>

#define B_P PIND & 0x04


int main()
{
  DDRD = 0xff; // PORT D est en mode sortie
  int haut = 0;
  int bas  = 2000; 

 while(haut != bas)
  { 
    for( int duree = 0; duree < 2000 ; duree++)
      {
        for (int i = 0; i < bas; i++)
          {
            PORTD = 0x00;
          }
        for (int j = 0; j < haut; j++)
          {
            PORTD = 0x01;
          }
        _delay_ms(1); 
      }
    haut +=250;
  }

return 0;  
} 
  