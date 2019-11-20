/*

Machine de Moore   Entree : Pression sur l'interrupteur ou minuterie est expirée
                   Sortie : Couleur et agissement de la led


  Etat actuel |  Entree   | Sortie               |  Etat Suivant


       0      |     1     |  Vert                |    1

       1      |     1     |  Clignotement rouge  |    2

       2      |     1     |   Vert               |    3

       3      |     1     |  Éteint              |    -

*/
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define BUTTON_IS_PRESSED PIND & 0X04
#define VERT 0X02
#define ROUGE 0x01
#define ETEINT 0x00

volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir=0; 
volatile uint16_t compteur=0;

void initialisation(){
  DDRA = 0xff; // PORT A est en mode sortie  
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entree
  // cette procédure ajuste le registre EIMSK
  // de l’ATmega324PA pour permettre les interruptions externes
  EIMSK |= (1 << INT0) ;
  // il faut sensibiliser les interruptions externes aux
  // changements de niveau du bouton-poussoir
  // en ajustant le registre EICRA
  EICRA |= (1 << ISC00) ;
  // sei permet de recevoir à nouveau des interruptions.
  sei ();
}

void partirMinuterie (uint16_t duree) {
  minuterieExpiree = 0;
// mode CTC du timer 1 avec horloge divisée par 64
// interruption après la durée spécifiée
  TCNT1 = 0;
  OCR1A = duree;
  TCCR1A = (1 << COM1A1)|(1 <<COM1A0);
  TCCR1B = (1 << CS11)|(1<<CS10)|(1<<WGM12);
  TCCR1C = 0;
  TIMSK1 = (1 << OCIE1A);
}

void actionEtat(uint8_t etat)
{
  switch (etat)
  {
    case (0) : PORTB=VERT;
               _delay_ms(500);
               PORTB=ETEINT;
               _delay_ms(2000);
            break;
    case(1)  : for(uint8_t i=0;i<compteur/2;++i)
               {
                  PORTB=ROUGE;
                  _delay_ms(450);PORTB=ETEINT;
                  _delay_ms(50);
               }
            break;
    case(2)   : PORTB=VERT;
                _delay_ms(1000);
            break;
    case(3): PORTB=ETEINT;
            break;
  }
}

int main()
{ 
  int etat=0;
  initialisation();
  while(boutonPoussoir!=1){} //rien faire au debut -> bouton n'est pas presse 
  while(boutonPoussoir==1 && compteur!=120) //incremente le compteur tant que le bouton est enfonce et compteur n'est pas arrive a 120
  {
    partirMinuterie(12500);
    while(minuterieExpiree==0){} //on veut pas que TCNT1 soit remis a zero avant l'expiration de la minuterie 
    compteur++;
  }
  while(etat<4) //boucle pour effectuer les actions de chaque etat
  {
    actionEtat(etat);
    etat++; //on passe au prochain etat
  }
}

ISR (TIMER1_COMPA_vect) {
  minuterieExpiree = 1;
}


ISR (INT0_vect) {
  if(boutonPoussoir==0) 
  {
    boutonPoussoir=1; //boutonpoussoir=1 signifie qu'il est enfonce puisque il egale a zero par default voir l'initialisation des volatiles 
    _delay_ms ( 30 );
  } 
  else 
  { 
    boutonPoussoir=0; //boutonpoussoir=0 signifie que est relache
    _delay_ms ( 30 ); 
  }
}