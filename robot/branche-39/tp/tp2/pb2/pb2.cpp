/*

Machine de Mealy   Entree : Pression sur l'interrupteur 
				           Sortie : Couleur de la led si allumee 


	Etat actuel	|  Entree	  |	Sortie	|  Etat Suivant


	  Initial	  |	    0		  |	 Rouge	|    Initial

	  Initial	  |	    1	  	|	 Ambre	|      E1

	     E1	    |	    0	  	|	  Vert	|      E1

	     E1	    | 	  1	    |	 Rouge	|      E2

	     E2	    |  	  0	   	|	 Eteint	|      E2

	     E2	    |	    1	   	|	  Vert	|    Initial

*/

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define BUTTON_IS_PRESSED PIND & 0X04
#define VERT 0X02
#define ROUGE 0x01
#define ETEINT 0x00
volatile unin8_t etat=0;

enum Machine
{
  INIT1,E1,E2
};

void changerEtat(Machine& a)
{
  switch(a){

    case INIT1 : a=E1;
            break;

    case E1 : a=E2;
            break;

    default : a=INIT1;

  }
}
void actionEtat(Machine a)
{
  switch(a){

    case INIT1 :  
            while(BUTTON_IS_PRESSED) {
              _delay_ms(10); 
              PORTB=VERT;};
            while(!(BUTTON_IS_PRESSED)){
              _delay_ms(10);
              PORTB=ROUGE;
            };
            break;

    case E1 : 
            while(BUTTON_IS_PRESSED) {
              _delay_ms(20); 
              PORTB=ROUGE;
              _delay_ms(10);
              PORTB=VERT;
            };
            while(!(BUTTON_IS_PRESSED)){
              PORTB=VERT;
            };
            break;

    default : while(BUTTON_IS_PRESSED) { // Ou E2
             _delay_ms(10); PORTB=ROUGE;
            }; 
            while(!(BUTTON_IS_PRESSED)){
              PORTB=ETEINT;
            };
            
    }
}
// placer le bon type de signal d'interruption

// à prendre en charge en argument

ISR (PCINT1_vect) {

// laisser un delai avant de confirmer la réponse du

// bouton-poussoir: environ 30 ms (anti-rebond)

_delay_ms ( 30 );

// se souvenir ici si le bouton est pressé ou relâché

'modifier ici'

// changements d'états tels que ceux de la

// semaine précédente

'modifier ici'

// Voir la note plus bas pour comprendre cette instruction et son rôle

EIFR |= (1 << INTF0) ;

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
    actionEtat(Test);       
    changerEtat(Test); 
  }
  
  return 0; 
}