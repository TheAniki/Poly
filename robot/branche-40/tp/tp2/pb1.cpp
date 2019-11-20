/*
Auteurs : Ouassim Ouali et Kevin Wassef
________________________________________________________
| Etat present | Entree | Etat suivant |    Sortie Z   |
|     INIT     |   0    |     INIT     |   N/A couleur |
|     INIT     |   1    |     Etat 1   |   N/A couleur |
|     Etat 1   |   0    |     Etat 1   |   N/A couleur |
|     Etat 1   |   1    |     Etat 2   |   N/A couleur |
|     Etat 2   |   0    |     Etat 2   |   N/A couleur |
|     Etat 2   |   1    |     Etat 3   |   N/A couleur |
|     Etat 3   |   0    |     Etat 3   |   N/A couleur |
|     Etat 3   |   1    |     Etat 4   |   N/A couleur |
|     Etat 4   |   0    |     Etat 4   |   N/A couleur |
|     Etat 4   |   1    |     Etat 5   |   N/A couleur |
|     Etat 5   |   0    |     Etat 5   | couleur rouge |
|     Etat 5   |   1    |      INIT    |   N/A couleur |
________________________________________________________
*/

#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>

#define B_P PIND & 0x04

int main()
{
  DDRA = 0xff; // PORT B est en mode sortie
  int etat=0; //etat initial
 
  for(;;)  // boucle sans fin
  { 
     

        
        if (B_P){
        _delay_ms(10);
            if (B_P)
            {
             etat++;
                while(B_P){ }                                
            } 
        } 
                switch(etat) {
                 case 1: PORTA = 0x00; break; // etat 1
                 case 2: PORTA = 0x00; break; // etat 2
                 case 3: PORTA = 0x00; break; // etat 3
                 case 4: PORTA = 0x00; break; // etat 4
                 case 5:                      // etat 5
                 PORTA = 0x02;
                 _delay_ms(1000); 
                 PORTA = 0x00;
                 etat = 0; // retour a l'etat init
                 break;                          
         }
      }
       return 0; 
    } 