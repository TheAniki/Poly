/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme 
 * Version: 1.1
 */


#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>
int main()
{
  DDRB = 0xff; // PORT B est en mode sortie
  for(;;)  // boucle sans fin
  {
    PORTB = 0x01;
    _delay_ms(1000);
    PORTB = 0x02;
    _delay_ms(1000);
    for(int i=0 ; i<300 ; i++){
      PORTB=0x01;
      _delay_ms(2);
      PORTB=0x02;
      _delay_ms(1);

    }
  }
  return 0; 
}
