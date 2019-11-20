#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#define BUTTON_IS_PRESSED PIND & 0X04
#define ROUGE 0X01
#define VERT 0X02
#define ETIENT 0X00

void my_delay(uint16_t const& NbOf30Us)
{
  for(uint16_t j=0;j<NbOf30Us;j++)
  {
    _delay_us(30);
  }
}
int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0xff; // PORT D est en mode sortie
  PORTB=0X00;   
  PORTB=PORTB<<2;
  uint16_t const& b=1000; //us
  for(;;)  // boucle sans fin
  {
    uint16_t a=1000;
    for(uint16_t i=0;i<3000;++i)
    {
      if((i+1)%3==0)
      {
        --a;
      }
      PORTB=ROUGE;
      my_delay(int(a/30));
      PORTB=ETIENT;
      my_delay(int((b-a)/30));
    }
  }
}