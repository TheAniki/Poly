
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> //POUR L'INTERRUPTEUR
using namespace std;



/*ISR (TIMER1_COMPA_vect) //ask
{
	minuterieExpiree = 1;
}


ISR (INT0_vect) //code prob1 
{
	boutonPoussoir = 1;
	// anti-rebond
	_delay_ms(30);
	EIFR |= (1 << INTF0) ;
}


void initialisation ( void ) //code prob1
{
  cli (); 
	DDRA = 0XFF;
	DDRD = 0x00;  
  EIMSK |= (1 << INT0) ;
  EICRA |= ( 1 << ISC01);
  sei ();
}

void partirMinuterie ( uint16_t duree ) 
{
	minuterieExpiree = 0;
	// mode CTC du timer 1 avec horloge divisée par 1024
	// interruption après la durée spécifiée
	TCNT1 = 0; //valeur initiale du compteur
	OCR1A = duree;//comparer la valeur avec TCNT1
	
	TCCR1A |= (1 << COM1A1)  ;
	TCCR1A |= (1 << COM1A0) ;
	
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS12);
	TCCR1B |= (1 << CS10);
	
	TCCR1C = 0; 
	
	TIMSK1 |= (1 << OCIE1A); 
}


int main ()
{
	initialisation();
	
	_delay_ms(10000);//10 seconde
	PORTA= 0x01;//DEL rouge
	_delay_ms(100);//0.1 sec
	PORTA = 0x00; //DEL eteint
	partirMinuterie(0X1E84); //7812 ??? 
	
 while ( !minuterieExpiree  && !boutonPoussoir )
 {}

//verification 

if (minuterieExpiree==0)
{
	PORTA=0x02;//DEL_VERT
}
else 
{
	PORTA=0x01; //DEL_ROUGE
}

	return 0; 
}*/


#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define BUTTON_IS_PRESSED PIND & 0X04
#define VERT 0X02
#define ROUGE 0x01
#define ETEINT 0x00
volatile uint8_t etat;
//volatile uint8_t etat = 0;
volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir; 
void initialisation(){
  DDRA = 0xff; // PORT A est en mode sortie  
  DDRB = 0xff; // PORT B est en mode sortieI
  DDRC = 0xff; // PORT C est en mode sortieI
  DDRD = 0x00; // PORT D est en mode entreeI
  // cette procédure ajuste le registre EIMSKI
  // de l’ATmega324PA pour permettre les interruptions externesI
  EIMSK |= (1 << INT0) ;
  // il faut sensibiliser les interruptions externes auxI
  // changements de niveau du bouton-poussoir
  // en ajustant le registre EICRA
  EICRA |= (1 << ISC00) ;
  // sei permet de recevoir à nouveau des interruptions.
  sei ();
}

void actionEtat()
{
 
  // Une interruption s'est produite. Arrêter tout
  // forme d'interruption. Une seule réponse suffit.
  cli ();
  // Verifier la réponse
  if(minuterieExpiree==0)
  {
    PORTB=VERT;
  }
  else
  {
    switch (etat)
    {
    case (0): PORTB=0X00;
      break;
    case (1): PORTB=0X01;
      break;
    case (2): PORTB=0x02;
      break;
    default:
      break;
    }
  }
  
}
void partirMinuterie (uint16_t duree ) {
  minuterieExpiree = 0;
// mode CTC du timer 1 avec horloge divisée par 1024
// interruption après la durée spécifiée
  TCNT1 = 0;
  OCR1A = duree;
  TCCR1A = (1 << COM1A1)|(1 <<COM1A0) ;
  TCCR1B = (1 << CS12) | (1<<CS10)|(1 << WGM12) ;
  TCCR1C = 0;
  TIMSK1 = (1 << OCIE1A);
}

int main(){
  for(;;)
  {
    do {

  // attendre qu'une des deux variables soit modifiée

  // par une ou l'autre des interruptions.

    } while ( minuterieExpiree == 0 && boutonPoussoir == 0 );
    partirMinuterie(0x1E84);
    if(boutonPoussoir==1)
    {
      actionEtat();
    }
    if(minuterieExpiree==1)
    {
      PORTB=ROUGE;
    }
  }
}
ISR (TIMER1_COMPA_vect) {
  minuterieExpiree = 1;
}

ISR (INT0_vect) {
  boutonPoussoir = 1;
  // anti-rebond
  _delay_ms ( 30 ); 
  etat++;
  if(etat==2)
  {
    etat=-1;
  }
}