                                                                   
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
volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir; 

ISR ( TIMER1_COMPA_vect  ) {

minuterieExpiree = 1;

}


ISR ( INT0_vect ) {

boutonPoussoir = 1;

// anti-rebond

_delay_ms (10);

EIFR |= (1 << INT0) ;
}

void partirMinuterie (uint16_t duree) {

minuterieExpiree = 0;

// mode CTC du timer 1 avec horloge divisée par 1024

// interruption après la durée spécifiée

TCNT1 = 0 ;

OCR1A = duree;

TCCR1A = (1 << COM1A1) ;

TCCR1B = (1 << COM1A0) ;

TCCR1C = 0;

TIMSK1 = (1 << OCIE1A) ;

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

// cette procédure ajuste le registre EIMSK

// de l’ATmega324PA pour permettre les interruptions externes

EIMSK |= (1 << INT0) ;


// il faut sensibiliser les interruptions externes aux

// changements de niveau du bouton-poussoir

// en ajustant le registre EICRA

EICRA |= (1<< ISC01);


// sei permet de recevoir à nouveau des interruptions.

sei ();

}

int main()					  
{
  initialisation();                   
             
  do { PORTA=0x00;
      _delay_ms (10000);
      PORTA=0x01;
      _delay_ms(100);


// attendre qu'une des deux variables soit modifiée

// par une ou l'autre des interruptions.

} while ( minuterieExpiree == 0 && boutonPoussoir == 0 );


// Une interruption s'est produite. Arrêter toute

// forme d'interruption. Une seule réponse suffit.

cli ();

// Verifier la réponse
if (minuterieExpiree != 0 && boutonPoussoir != 0)
{
  PORTA = ROUGE;
}


	return 0; 
}