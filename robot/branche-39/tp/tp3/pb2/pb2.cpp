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
int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0xff; // PORT D est en mode sortie
  PORTB=0X00;   
  PORTB=PORTB<<2;
  uint32_t const& b60hz=16667;
  uint16_t const& b400hz=2500;
  for(;;)  // boucle sans fin
  {
    uint16_t a400hz=0;
    uint32_t a60hz=0;
    boucle60hz(a60hz,b60hz);
    boucle400hz(a400hz,b400hz);
  }
}