                                                                   
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

void ajustementPWM ( float haut, float bas) {


TCNT1 = 0; 

OCR1A = static_cast<uint8_t>(haut*UINT8_MAX) ;

OCR1B = static_cast<uint8_t>(bas*UINT8_MAX) ;


TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10) ;

TCCR1B = (1<<CS11);

TCCR1C = 0;

}

int main()					  
{
  initialisation();  

  ajustementPWM(0,0);
  _delay_ms(2000);

  ajustementPWM(0.25,0.75);
  _delay_ms(2000);

  ajustementPWM(0.5,0.5);
  _delay_ms(2000);

  ajustementPWM(0.75,0.25);
  _delay_ms(2000);

  ajustementPWM(1,0);
  _delay_ms(2000); 

  ajustementPWM(0,0);
  

	return 0; 
}