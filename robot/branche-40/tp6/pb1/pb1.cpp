/*	Auteurs: Ouassim Ouali et Kevin Wassef
	equipe :  40
	tp6 probleme 1: Ce programme permet de controler une DEL à partir d'un bouton-poussoir externe
					suivant un cycle predetermine (Voir TP6).


	Utilisation des broches : Le cable rouge et noir est relié au PORTB, le fil rouge etant connecté au VCC et
							  le fil noir au GND.

							  Le cable bleu et brun sont connectes au PORTD, le fil bleu étant connecté au port D2 et
							  le brun au port D3.

							  La DEL est connectee au PORTB a A0 et A1.
*/


#define F_CPU 8000000	
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>  //Permet l'utilisation d'un interrupteur

using namespace std;

const uint8_t ETEINTE = 0x00;
const uint8_t ROUGE = 0x01;
const uint8_t VERTE = 0x02;
const uint8_t SORTIE = 0xFF;
const uint8_t ENTREE = 0x00;
volatile uint8_t ETAT = 0;

void initialisation()
{
  cli();		 //Permet de bloquer les interruptions
  DDRD = ENTREE; // initialisation des pin de D en entree 
  DDRA = SORTIE; //initialisation des pin de A en sortie

  EIMSK |= (1 << INT0);  //Permet les interruptions externes
  EICRA |= (1 << ISC00); //Permet les changements de niveaux aux interruptions externes

  sei();  //Permet de recevoir a nouveau les interruptions
}

ISR(INT0_vect) //signal d'interruption
{
        _delay_ms(10); //anti-rebond

        if (ETAT == 3) //changement d'etat
        {
            ETAT = 0;
        }
        else
        {
            ETAT++;
        }
        EIFR |= (1 << INTF0);  //Permet a l'AVR de se souvenir d'une interruption
							   //qui se produirait durant une autre interruption
							   //et de l'executer lorsque lorsque celle en cours sera terminé
}


int main()
{
initialisation();
int compteur=0;

while (true)
{
    switch (ETAT)		//Permet d'effectuer la bonne action selon l'etat actuelle du programme
    {
    case 0:
        PORTA = ETEINTE;
        break;
    
    case 1:                 //Permet d'incrementer un compteur a un taux de 10 incrementations par secondes.
        if (compteur<120)   //La valeur maximale que le compteur peut atteindre est 120.
        {
            compteur++;
            _delay_ms(100);		// delais de 100 ms 
        }
        else
        {			
            ETAT=2;		//changement d'etat si la valeur du compteur atteint 120.
        }
        break;
    
    case 2:
        for (int i=0; i<3; i++)  //Permet de faire clignoter la del en la couleur verte pendant 1/2 seconde
        { 
			PORTA = VERTE;
			_delay_ms(100);		// delais de 100 ms 

			PORTA=ETEINTE;
			_delay_ms(50);		// delais de 50 ms 
		}	
				ETAT = 3;				
				break;
    
    case 3:
        _delay_ms(2000);					 //delai de 2 secondes

        for (int i = 0; i < compteur/2; i++) //Permet de faire clignoter la del en rouge 2 fois par seconde
        {
            PORTA=ROUGE;
            _delay_ms(250);		// delais de 250 ms 

            PORTA=ETEINTE;
			_delay_ms(250);		// delais de 250 ms 
		}	
        
            PORTA=VERTE;
            _delay_ms(1000);	// delais de 1 seconde 

            ETAT=0;				//Retour a l'etat original
        break;

    default:
        break;
    }
}

    return 0;
}