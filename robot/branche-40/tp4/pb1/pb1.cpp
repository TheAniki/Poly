                                                                   
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h> 
#define Button_Pressed PIND & 0x04

const uint8_t PortSortie = 0xFF;
const uint8_t PortEntree = 0x00;
const uint8_t ETEINTE = 0x00;
const uint8_t ROUGE = 0x01;
const uint8_t VERTE = 0x02;
volatile uint8_t etat = 0; //etat initial

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
ISR ( INT0_vect ) {


// laisser un delai avant de confirmer la réponse du

// bouton-poussoir: environ 30 ms (anti-rebond)

_delay_ms ( 30 );

// se souvenir ici si le bouton est pressé ou relâché




// changements d'états tels que ceux de la

// semaine précédente

if(etat == 5)
{
  etat = 0;
}
else
{
  etat++;
}

// Voir la note plus bas pour comprendre cette instruction et son rôle

  EIFR |= (1 << INTF0) ;

}

void initialisation ( void ) {

// cli est une routine qui bloque toutes les interruptions.

// Il serait bien mauvais d'être interrompu alors que

// le microcontroleur n'est pas prêt...

cli ();


// configurer et choisir les ports pour les entrées

// et les sorties. DDRx... Initialisez bien vos variables
  DDRD = PortEntree;
  DDRA = PortSortie; // PORT B est en mode sortie
  PORTA = VERTE;   


// cette procédure ajuste le registre EIMSK

// de l’ATmega324PA pour permettre les interruptions externes

EIMSK |= (1 << INT0) ;


// il faut sensibiliser les interruptions externes aux

// changements de niveau du bouton-poussoir

// en ajustant le registre EICRA

EICRA |= (1<< ISC00);


// sei permet de recevoir à nouveau des interruptions.

sei ();

}

int main()					  
{
  initialisation();
  for(;;)  // boucle sans fin
  {                   
             
        switch(etat) {     //machine a etat
             case 1:    
                 while(Button_Pressed){ambre();}
                 etat++;                    
                 break;
             case 2: PORTA = ROUGE; break; 
             case 3: while(Button_Pressed){PORTA = VERTE;} etat++; break;
             case 4: PORTA = ETEINTE; break;
             case 5: while(Button_Pressed){PORTA = ROUGE;}
                    PORTA = VERTE; break;      
         }
  }
 return 0; 
}