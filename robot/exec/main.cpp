#define F_CPU 8000000
#include "PWMDEL.h"
#include "PWM_roue.h"
#include <util/delay.h>
#include <avr/io.h>
//#include "debug.h"
#include "transmissionChaineUART.h"
#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"
//#include "sonar.h"
#include "operation.h"
#include "Son.h"
#include "customprocs.h"
#include <stdlib.h>
#include <stdio.h>

#define capteur1 PINA & 0x01
#define capteur2 PINA & 0x02
#define capteur3 PINA & 0x04
#define capteur4 PINA & 0x08
#define capteur5 PINA & 0x10
#define DEMO_DDR	DDRC // `Data Direction Register' AVR occup� par l'aff.
#define DEMO_PORT	PORTC // Port AVR occup� par l'afficheur
static uint8_t volatile etat=0;
static bool volatile debut=false;
static uint8_t volatile i=0;
static uint8_t volatile j=1;
static uint8_t volatile OVERFLOW=0;
static uint16_t volatile pulse=0;
bool Mur=false;
enum Etats{couloir,mur,boucle,coupure};
TransmissionChaineUART uart;
LCM disp(&DEMO_DDR, &DEMO_PORT);

void initialisationmain()
{
    cli();
    DDRA=0x00;
    DDRB=0b11111011;
    DDRD=0b11110011;
    TCCR2A=0;
    EIMSK=( (1<<INT0) | (1<<INT1) | (1<<INT2));
    EICRA=((1<<ISC11) | (1<<ISC00) | (1<<ISC20));
    sei();
}

void suivreMur(){
    while(!lireCapteurs())
    {
        PORTB |=(1<<PB3);
        _delay_us(10);
        PORTB &=~(1<<PB3);
        uint16_t distance=pulse/58;
        uart.transmissionUART(distance);
        _delay_ms(50);
		while(distance<15)
		{
			ajustementPWM (0,0.5);
			PORTB |=(1<<PB3);
        	_delay_us(10);
        	PORTB &=~(1<<PB3);
			distance=pulse/58;
            uart.transmissionUART(distance);
			_delay_ms(50);
            if(etat!=Etats::mur || lireCapteurs())
            {
                break;
            }
		}
		while(distance==15)
		{
			ajustementPWM (0.5,0.5);
			PORTB |=(1<<PB3);
        	_delay_us(10);
        	PORTB &=~(1<<PB3);
			distance=pulse/58;
            uart.transmissionUART(distance);
			_delay_ms(50);
            if(etat!=Etats::mur || lireCapteurs())
            {
                break;
            }
		}
		while(distance>15)
		{
			ajustementPWM (0.5,0);
			PORTB |=(1<<PB3);
        	_delay_us(10);
        	PORTB &=~(1<<PB3);
			distance=pulse/58;
            uart.transmissionUART(distance);              
			_delay_ms(50);
            if(etat!=Etats::mur || lireCapteurs())
            {
                break;
            }
		}
    }
}
void faireSectionCoupure()
{
    _delay_ms(20);disp.clear();disp[0]="les coupures";
    uint8_t compteur = 0;
    bool faire= true;
    while(faire)
    {
        faireCoupure();
        compteur++;
        if(compteur == 4)
        {
            faire = false;
        }
    }
    _delay_ms(20);disp.clear();disp[0]="fini coupure";
}
void faireSectionCouloir()
{
     _delay_ms(20);disp.clear();disp[0]="couloir";
    tournerUnPeuGauche();
    while(!lireCapteurs()){}
    arretMouvement();   
    bool faire= true;
    while(faire)
    {
        suivreCouloir();
        if(lireCapteur3()){faire =  false;}        
    }
    _delay_ms(20);disp.clear();disp[0]="fini couloir";
    arretMouvement();
    
}

int main()
{
    initialisationmain();
    uart.initialisationUART();
    
    //faireSectionCoupure();
    
        //suivreLigneSimplement();
        //faireCouloir(true);
        //suivreCouloir();
    
    faireSectionCouloir();
   
    
    // bool fin = !debut;
    // while(!fin)
    // {   
    //     switch (etat)
    //     {
    //     case Etats::couloir: _delay_ms(20); disp.clear(); disp[0]="le couloir";
    //         if(debut)
    //         {
    //             etat++;
    //         }
    //         break;
    //     case Etats::mur: _delay_ms(20); disp.clear(); disp[0]="le mur";
    //         if(debut)
    //         {   while(lireCapteurs())
    //             {
    //                 suivreLigneSimplement();
    //             }
    //             suivreMur();
    //             if (lireCapteurs())
    //             {
    //                 etat++;
    //             }
    //         }
    //         break;
    //     case Etats::boucle: _delay_ms(20); disp.clear(); disp[0]="les deux boucles";
    //         if(debut)
    //         {
    //             faireBoucle();
    //             etat++;
    //         }
            
    //         break;
    //     case Etats::coupure:
    //         if(debut)
    //         {                
    //             faireSectionCoupure();
    //             etat++;
    //         }         
    //         break;
    //     default:
    //         fin = true;
    //         arretMouvement(); // arret de tous les mouvements
    //         break;
    //     }
    // }   
   
    return 0;

}
ISR(INT0_vect)
{
    debut=true;
}
ISR(INT1_vect)
{
    if(!(PIND & 0x8))
    {
        _delay_ms(10);
        while(!(PIND & 0x8)){};
    }
    if(j%2)
    {
        ++etat;
    }
    if(etat> Etats::coupure)
    {
        etat=0;
    }
    j++;
}
ISR(INT2_vect)
{
	if(i==1)
	{
		TCCR2B=0;
		TIMSK2 &=~(1<<TOIE2); // no clock source/on arrete le compteur 
        pulse=TCNT2+256*OVERFLOW; 
        TCNT2=0;
        i=0;	
    }
    if (i==0)
    {
		OVERFLOW=0;
        TCCR2B|=(1<<CS21);
		TIMSK2 |= (1<<TOIE2); //clock/8 --> tcnt1 incremente chaque 1 microseconde simplifie le calcul pas besoin de convertir le pulse
        i=1;
    }
}

ISR(TIMER2_OVF_vect) 
{
	++OVERFLOW;
}