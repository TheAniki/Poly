#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>

#define B_P PIND & 0x04

/*
_________________________________________________________
| Etat present | Entree | Etat suivant |    Sortie Z    |
|    Init	   |    0   |     init     |  couleur rouge |
|    Init	   |    1   |    etat 1    |  couleur ambre |
|    Etat 1	   |    0   |    etat 2    |  couleur verte |
|    Etat 1	   |    1   |    etat 1    |  couleur ambre |
|    Etat 2	   |    0   |    etat 2    |  couleur verte |
|    Etat 2	   |    1   |    etat 3    |  couleur rouge |
|    Etat 3	   |    0   |    etat 4    |      eteint    |
|    Etat 3	   |    1   |    etat 3    |  couleur rouge |
|    Etat 4	   |    0   |    etat 4    |     eteint     |
|    Etat 4	   |    1   |    etat 5    | couleur verte  |
|    Etat 5	   |    0   |     init     | couleur rouge  |
|    Etat 5    |    1   |    etat 5    | couleur verte  |
_________________________________________________________
*/

void ambre() //couleur ambre
{
   
                 PORTA=0x01;
                 _delay_ms(2);
                 PORTA=0x02;  
                _delay_ms(1); 
            				  
}							  
int main()					  
{
  DDRA = 0xff; // PORT B est en mode sortie
    PORTA = 0x02;
  int etat=0; //etat initial
    
  for(;;)  // boucle sans fin
  { 
             
           if (B_P){		//anti-rebond
         _delay_ms(10);
             if (B_P)
            {
              etat++;
                while(B_P){ break;}
                                             
         } 
         }    
                 switch(etat) {     //machine a etat
                    case 1:    
                     while(B_P){ambre();}
                    etat++;                    
                     break;
                    case 2: PORTA = 0x01; break; 
                    case 3: while(B_P){PORTA = 0x02;} etat++; break;
                    case 4: PORTA = 0x00; break;
                    case 5: while(B_P){PORTA = 0x01;} PORTA = 0x02; etat = 0; break;   //retour a init    
         }
      }
       return 0; 
    }