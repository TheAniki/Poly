#include "PWM_roue.h"

#define Button_Pressed PIND & 0x04

const uint8_t portSortie = 0xFF;
const uint8_t portEntree = 0x00;

void initialisation()
{
  cli();
  DDRD = portSortie;
  DDRA = portSortie;
  sei();  
}

void ajustementPWM ( float vitesse1, float vitesse2) //On les ajustes en PWM selon nos deux vitesses
{
  TCNT1 = 0; 
  OCR1A = static_cast<uint8_t>(vitesse1*UINT8_MAX) ;
  OCR1B = static_cast<uint8_t>(vitesse2*UINT8_MAX) ;
  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10) | (1<< WGM12);
  TCCR1B = (1<<CS11);
  TCCR1C = 0;
}

void accelerer() //Acceleration jusqu a 100% avec augmentation de 25% par 2 secondes
{
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
  PORTD=(0X00<<6);
  ajustementPWM(vitesse,vitesse);
}

void ajustementPWMmoteur(float vitesse)
{
  TCNT1 = 0; 

  OCR1A = static_cast<uint8_t>(vitesse*UINT8_MAX) ;

  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10) | (1<< WGM12);

  TCCR1B = (1<<CS11);

  TCCR1C = 0;

}