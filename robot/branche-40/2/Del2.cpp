#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>
int main()
{
  DDRB = 0xff; // PORT B est en mode sortie
  for(;;)  // boucle sans fin
  {
    // PORTB = 0x01;
    // _delay_ms(1000);
    // PORTB = 0x02;
    // _delay_ms(1000);

    if (PIND & 0x04){
        _delay_ms(10);
        while(PIND & 0x04){ 
        
            for(int i=0 ; i<10 ; i++){
                 PORTB=0x01;
                 _delay_ms(2);
                 PORTB=0x02;
                _delay_ms(1);
            }
         PORTB = 0x00;
        }
    }
  }
  return 0; 
}

