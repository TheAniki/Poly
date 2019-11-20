#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#define BUTTON_IS_PRESSED PIND & 0X04
#define ROUGE 0X01
#define VERT 0X02
#define ETIENT 0X00

void my_delay(uint16_t const& NbOf25Us)
{
  for(uint16_t j=0;j<NbOf25Us;j++)
  {
    _delay_us(25);
  }
}
void boucle60hz(uint32_t a,uint32_t b)
{
  for(uint16_t i=0;i<600;++i)
  {
    uint8_t const& taux=25;
    if((i+1)%120==0)
    { 
      a=(taux*((i+1)/120)*b)/100;
    }
    PORTB=0X01;
    my_delay(a/25);
    PORTB=0X00;
    my_delay((b-a)/25);
  }
}
void boucle400hz(uint16_t a,uint16_t b)
{
  for(uint16_t i=0;i<4000;++i)
  {
    uint8_t const& taux=25;
    if((i+1)%800==0)
    { 
      a=(taux*((i+1)/800)*b)/100;
    }
    PORTB=0X01;
    my_delay(a/25);
    PORTB=0X00;
    my_delay((b-a)/25);
  }
}
