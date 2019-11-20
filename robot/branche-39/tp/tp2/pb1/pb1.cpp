/*

Machine de Moore   Entree : Pression sur l'interrupteur
				           Sortie : Couleur de la led si allumee


	Etat actuel	|  Entree	 |	Sortie	|  Etat Suivant


	   INIT1	  |	    0		 |	Eteint	|     INIT1

	   INIT1  	|	    1	   |	Eteint	|      E1

		   E1	    |	    0	 	 |	Eteint	|      E1

		   E1	    | 	  1		 |	Eteint	|      E2

		   E2	    |  	  0		 |	Eteint	|      E2

		   E2	    |	    1		 |	Eteint	|      E3

		   E3	    |	    0 	 |	Eteint	|      E3

		   E3	    | 	  1		 |	Eteint	|      E4

		   E4	    |  	  0		 |	Eteint	|      E4

		   E4	    |	    1		 |	Eteint	|      E5

		   E5	    |	    X		 |	Rouge   |     INIT1

*/

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#define BUTTON_IS_PRESSED PIND & 0X04
#define VERT 0X02
#define ROUGE 0x01
#define ETEINT 0x00

enum Machine
{
  INIT1,E1,E2,E3,E4,E5
};

void changerEtat(Machine& a)
{
  switch(a){
    case INIT1 : a=E1;
            break;
    case E1 : a=E2;
            break;
    case E2 : a=E3;
            break;
    case E3 : a=E4;
            break;
    case E4 : a=E5;
            break;
    default : a=INIT1;
  }
}
void actionEtat(Machine a)
{
  if(a==E5)
  {
    PORTB=ROUGE;
    _delay_ms(1000);
    PORTB=ETEINT;
  }
  else
  {
    PORTB=ETEINT;
  }
}

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode sortie
 
  Machine Test=INIT1;
  for(;;)  // boucle sans fin
  {
    PORTB=0X00;

    if(BUTTON_IS_PRESSED)
    {
      _delay_ms(10);
        if(BUTTON_IS_PRESSED)
        {
          _delay_ms(10);
          while(BUTTON_IS_PRESSED);
        changerEtat(Test);
        actionEtat(Test);
        if(Test==E5)
          {
            changerEtat(Test);
          }
        
        } 
    }
  }
  
  return 0; 
}