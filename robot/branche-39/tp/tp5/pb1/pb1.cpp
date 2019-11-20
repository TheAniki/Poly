#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <memoire_24.h>
using namespace std;

int main()
{
  DDRB=0XFF;
  uint8_t chaine[]="*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
  Memoire24CXXX test;
  test.ecriture(0x00,chaine,sizeof(chaine)/sizeof(chaine[0]));
  _delay_ms(5);
  uint8_t chaineALire[sizeof(chaine)/sizeof(chaine[0])]={};
  test.lecture(0x00,chaineALire,sizeof(chaine)/sizeof(chaine[0]));
  bool egale=true;
  for(unsigned i=0;i<sizeof(chaine)/sizeof(chaine[0]);i++)
  {
    if(chaine[i]==chaineALire[i] && egale)
    {
      egale=true;
    }
    else
    {
      egale=false;
    }
  }
  if(egale)
  {
    PORTB=0X01;
  }
  else
  {
    PORTB=0X02;
  }
}