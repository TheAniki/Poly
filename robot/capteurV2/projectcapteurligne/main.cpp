#define F_CPU 8000000
#include "PWMDEL.h"
#include "PWM_roue.h"
#include <util/delay.h>
#include <avr/io.h>
#include "debug.h"
#include "transmissionChaineUART.h"
#include <stdlib.h>
#include <stdio.h>
#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"
#include "can.h"

enum etat{couloir,mur,boucle,coupures,Transition};
static volatile uint8_t i=0;
static volatile uint16_t pulse=0;
static volatile uint16_t OVERFLOW=0;
#define DEMO_DDR	DDRC // `Data Direction Register' AVR occup� par l'aff.
#define DEMO_PORT	PORTC // Port AVR occup� par l'afficheur
#define GAUCHE
#define DROITE 
#define RIEN 

void static inline w(void) {
	cp_wait_ms(2000);
}

// Plus gros d�mos :
static void banner(LCM&, char*, uint16_t);
static void wave(LCM&, uint16_t, uint16_t);

void lirecapteur(uint8_t (&capteur)[5])
{
	can test;
	for(unsigned i=0;i<5;++i)
	{
		capteur[i] = (uint8_t)(test.lecture(i)>>2);
	}
}
void avanceCouloir(uint8_t (&capteur)[5])
{
	for(;;)
	{
		if(!(capteur[0]&&capteur[1]&&capteur[2]&&capteur[3]&&capteur[4]&&capteur[5]))
		{
			ajustementPWM(0.5,0.5);
			lirecapteur(capteur);
			_delay_ms(10);
			while (!(capteur[0]&&capteur[1]&&capteur[2]&&capteur[3]&&capteur[4]&&capteur[5]));
		}
		if(capteur[0] || capteur[0]&&capteur[1] || capteur[0]&&capteur[1]&&capteur[2])
		{
			_delay_ms(10);
			while(capteur[0] || capteur[0]&&capteur[1] || capteur[0]&&capteur[1]&&capteur[2])
			{
				ajustementPWM(0.5,0.2);
				lirecapteur(capteur);
			}
		}

	}
}

void avancer(uint8_t (&capteur)[5])
{
	LCM disp(&DEMO_DDR, &DEMO_PORT);
	if((capteur[2] || capteur[2]&&capteur[1]&&capteur[3]) && (!capteur[0] && !capteur[4]))
	{
		//_delay_ms(10);
		while((capteur[2] || capteur[2]&&capteur[1]&&capteur[3]) && (!capteur[0] && !capteur[5]))
		{
			disp[16]="avance";
			ajustementPWM(0.8,0.8);
			lirecapteur(capteur);
		}
		disp.clear();
	}
	if((capteur[0] || capteur[0]&&capteur[1] || capteur[1]&&capteur[0]&&capteur[2]) && !capteur[3] && !capteur[4] )
	{
		//_delay_ms(10);
		while((capteur[0] || capteur[0]&&capteur[1] || capteur[1]&&capteur[0]&&capteur[2]) && !capteur[3] && !capteur[4])
		{
			disp[16]="gauche";
			ajustementPWM(0.8,0.4);
			lirecapteur(capteur);
		}
		disp.clear();
	}
	if((capteur[4] || capteur[4]&&capteur[3] || capteur[4]&&capteur[3]&&capteur[2]) && !capteur[1] && !capteur[0])
	{
		//_delay_ms(10);
		while((capteur[4] || capteur[4]&&capteur[3] || capteur[4]&&capteur[3]&&capteur[2]) && !capteur[1] && !capteur[0])
		{	
			disp[16]="droite";
			ajustementPWM(0.4,0.8);
			lirecapteur(capteur);
		}
		disp.clear();
	}
	/*if((capteur[0]&&capteur[1]&&capteur[2]&&capteur[3]&&capteur[4]))
	{
		_delay_ms(10);
		while((capteur[0]&&capteur[1]&&capteur[2]&&capteur[3]&&capteur[4]))
		{
			disp[16]="fuck";
			ajustementPWM(0.8,0.4);
			lirecapteur(capteur);
		}
		disp.clear();
	}*/
	/*if((capteur[0]&&capteur[1]&&capteur[2]&&capteur[3]&&capteur[4]) || !(capteur[0]&&capteur[1]&&capteur[2]&&capteur[3]&&capteur[4]))
	{
		_delay_ms(10);
		while((capteur[0]&&capteur[1]&&capteur[2]&&capteur[3]&&capteur[4]) || !(capteur[0]&&capteur[1]&&capteur[2]&&capteur[3]&&capteur[4]))
		{
			disp[16]="rien";
			ajustementPWM(0,0);
			lirecapteur(capteur);
		}
		disp.clear();
	}*/
	
}
void initregistre()
{
    DDRB=0XFF;
    DDRD=0xff;
	DDRA=0X00;
    //EIMSK=(1<<INT0);
    //EICRA=(1<<ISC00);
    //TCCR0A=0;
    sei();
}

int main()
{
    LCM disp(&DEMO_DDR, &DEMO_PORT);
	//can test;
	//uint8_t capteur[5];
    initregistre();
	auto sommeCritiqueTolal=255*5; //varie entre 231-235 on prend la valeur la plus basse
    float vitesseGAUCHE=1.0;
	float vitesseDROITE=1.0;
	char valeur[5];
	uint8_t capteur[5];
	for(;;)
    {
		lirecapteur(capteur);
		avancer(capteur);
		/*//avanceCouloir(capteur);
		sprintf(valeur,"%d",capteur[2]);
		disp[0]=valeur;
		disp[16]="verification";
		_delay_ms(50);
		disp.clear();
		if(capteur[2] || capteur[2]&&capteur[1] || capteur[2]&&capteur[3])
		{
			_delay_ms(10);
			while(capteur[2] || (capteur[2]&&capteur[1]) || (capteur[2]&&capteur[3]))
			{
				ajustementPWM(1,1);
				lirecapteur(capteur);
				disp[0]="avance";
				char valeur[4];
				sprintf(valeur,"%d",capteur[2]);
				disp[16]=valeur;
				_delay_ms(50);
				disp.clear();
			}
		}
		else
		{
			ajustementPWM(0,0);
		}*/
		
    }
}

/*ISR(INT0_vect)
{
    if (i==1)
    {   
		TCCR0B=0;
		TIMSK0 &=~(1<<TOIE0); // no clock source/on arrete le compteur 
        pulse=TCNT0+256*OVERFLOW; 
        TCNT0=0;
        i=0;	
    }
    if (i==0)
    {
		OVERFLOW=0;
        TCCR0B|=(1<<CS01);
		TIMSK0 |= (1<<TOIE0); //clock/8 --> tcnt1 incremente chaque 1 microseconde simplifie le calcul pas besoin de convertir le pulse
        i=1;
    }
}*/
/*ISR(TIMER0_OVF_vect) 
{
	++OVERFLOW;
}*/

/**
 * Fonction pour d�mo - banni�re de texte.
 *
 * @param lcm		R�f�rence vers un LCM
 * @param text		Texte � afficher (jeu de caract�res de l'afficheur)
 * @param ms_interval	Intervalle en millisecondes entre chaque d�callage
 */
static void banner(LCM& lcm, char* text, uint16_t ms_interval) {
	uint8_t start = 0, stop = 1, index = 0;
	uint16_t msg_len = cp_strlen(text);
	char t_char = 0;
	
	lcm.clear();
	cp_wait_ms(ms_interval);
	
	while (stop <= msg_len && start < msg_len - 1) {
		if (stop <= LCM_FW_HALF_CH) {
			index = LCM_FW_HALF_CH - stop;
		} else {
           	++start;
			index = 0;
		}
		
		t_char = text[stop];
		text[stop] = 0;
		lcm.write(text + start, index, stop == msg_len);
		text[stop] = t_char;

		if (stop != msg_len) {
			++stop;
		}

		cp_wait_ms(ms_interval);
	}
	
	lcm.clear();
	cp_wait_ms(ms_interval);
}

/**
 * Fonction pour d�mo - vague.
 *
 * @param lcm		R�f�rence vers un LCM
 * @param rep		Nombre de r�p�titions
 * @param ms_interval	Intervalle en millisecondes entre chaque mouvement
 */
static void wave(LCM& lcm, uint16_t rep, uint16_t ms_interval) {
	uint8_t t_per [8];
	
	for (uint8_t i = 0; i < 8; ++i) {
		for (uint8_t j = 0; j < 8; ++j) {
			if (j == i) {
				t_per[j] = 0xff;
			} else {
				t_per[j] = 0;
			}
		}
		lcm.build_cc(i, t_per);
	}
	
	char custom_l1 [] = "\x20\x07\x05\x04\x03\x02\x02\x01\x01\x01\x02\x02"
		"\x03\x04\x05\x07\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
		"\x20\x20\x20\x20\x20\x20\x07\x05\x04\x03\x02\x02\x01\x01\x01"
		"\x02\x02\x03\x04\x05\x07";
	char custom_l2 [] = "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
		"\x20\x20\x20\x20\x20\x08\x02\x03\x04\x05\x05\x06\x06\x06\x05"
		"\x05\x04\x03\x02\x08\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
		"\x20\x20\x20\x20\x20\x20";

	char t_char;
	
	lcm.clear();
	
	for (uint16_t k = 0; k < rep; ++k) {
		for (uint8_t i = 0; i < LCM_FW_TOT_CH; ++i) {
			t_char = custom_l1[i + 16];
			custom_l1[i + LCM_FW_HALF_CH] = 0;
			
			lcm.write(custom_l1 + i, 0);
			
			custom_l1[i + LCM_FW_HALF_CH] = t_char;
			t_char = custom_l2[i + LCM_FW_HALF_CH];
			custom_l2[i + LCM_FW_HALF_CH] = 0;
			
			lcm.write(custom_l2 + i, 16);
			
			custom_l2[i + LCM_FW_HALF_CH] = t_char;
			
			cp_wait_ms(ms_interval);
		}
	}
	
	lcm.clear();
}