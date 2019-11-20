#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void ajustementPWM (uint8_t vitesse100fois) {
// mise à un des sorties OC1A et OC1B sur comparaison
// réussie en mode PWM 8 bits, phase correcte
// et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
// page 177 de la description technique du ATmega324PA)
OCR1A = (vitesse100fois/100.0)*255;
OCR1B = (vitesse100fois/100.0)*255;
// division d'horloge par 8 - implique une frequence de PWM fixe

TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<WGM10);

TCCR1B = (1<<CS11);

TCCR1C = 0;

}
int main()
{
  DDRD=0xFF;
  for(int i=0;i<5;++i)
  {
    ajustementPWM(i*25);
    _delay_ms(2000);
    if(i*25==100)
    {
      i=0;
    }
  }
}
	
