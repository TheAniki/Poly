#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <PWM_roue.h>

#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>

#define Button_Pressed PIND & 0x04

const uint8_t PortSortie = 0xFF;
const uint8_t PortEntree = 0x00;

void initialisation()
{
  cli();
  DDRD = PortSortie;
  DDRA = PortSortie;
  sei();  

}

void ajustementPWM ( float vitesse1, float vitesse2) {
TCNT1 = 0; 

OCR1A = static_cast<uint8_t>(vitesse1*UINT8_MAX) ;

OCR1B = static_cast<uint8_t>(vitesse2*UINT8_MAX) ;


TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10) | (1<< WGM12);

TCCR1B = (1<<CS11);

TCCR1C = 0;

}

void accelerer()					  
{
  //initialisation();  

  ajustementPWM(0,0);
  _delay_ms(2000);

  ajustementPWM(0.25,0.25);
  _delay_ms(2000);

  ajustementPWM(0.5,0.5);
  _delay_ms(2000);

  ajustementPWM(0.75,0.75);
  _delay_ms(2000);

  ajustementPWM(1,1);
  _delay_ms(2000); 

  ajustementPWM(0,0);
}
void reculerVitesseConst(float vitesse)
{
  PORTD=(0x3<<6); //pour changer le sens de rotation 
  ajustementPWM(vitesse,vitesse);
}

void avancerVitesseConst(float vitesse)
{
  ajustementPWM(vitesse,vitesse);
}