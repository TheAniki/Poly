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

static volatile uint8_t i=0;
static volatile uint16_t pulse=0;
static volatile uint16_t OVERFLOW=0;
#define DEMO_DDR	DDRC // `Data Direction Register' AVR occup� par l'aff.
#define DEMO_PORT	PORTC // Port AVR occup� par l'afficheur

void static inline w(void) {
	cp_wait_ms(2000);
}

// Plus gros d�mos :
static void banner(LCM&, char*, uint16_t);
static void wave(LCM&, uint16_t, uint16_t);

void initregistre()
{
    //DDRB=0XFF;
    DDRB=0b11111011;
    EIMSK=(1<<INT2);
    EICRA=(1<<ISC20);
    TCCR2A=0;
    sei();
}

int main()
{
    LCM disp(&DEMO_DDR, &DEMO_PORT);
    TransmissionChaineUART uart;
    uart.initialisationUART();
    initregistre();
    while(1)
    {
        PORTB |=(1<<PB3);
        _delay_us(10);
        PORTB &=~(1<<PB3);
        uint16_t distance=pulse/58;
        uart.transmissionUART(pulse);
        char distanceASCII[10];
        //itoa(distance,distanceASCII,10);
        sprintf(distanceASCII,"%d",distance);
        disp[0]="Distance:";
        disp[9]=distanceASCII;
		disp[12]="cm";
		disp.clear(); 
        _delay_ms(50);
		ajustementPWM (1,1);
		while(distance>15)
		{
			disp.clear();
			ajustementPWM (0,0.5);
			PORTB |=(1<<PB3);
        	_delay_us(10);
        	PORTB &=~(1<<PB3);
			distance=pulse/58;
			sprintf(distanceASCII,"%d",distance);
			disp[0]="Distance:";
        	disp[9]=distanceASCII;
			disp[12]="cm";
			disp[16]="trouner a gauche";
			_delay_ms(50);
		}
		while(distance==15)
		{
			disp.clear();
			ajustementPWM (0.5,0.5);
			PORTB |=(1<<PB3);
        	_delay_us(10);
        	PORTB &=~(1<<PB3);
			distance=pulse/58;
			sprintf(distanceASCII,"%d",distance);
			disp[0]="Distance:";
        	disp[9]=distanceASCII;
			disp[12]="cm";
			disp[16]="ne rien faire";
			_delay_ms(50);
		}
		while(distance<15)
		{
			disp.clear();
			ajustementPWM (0.5,0);
			PORTB |=(1<<PB3);
        	_delay_us(10);
        	PORTB &=~(1<<PB3);
			distance=pulse/58;
			sprintf(distanceASCII,"%d",distance);
			disp[0]="Distance:";
        	disp[9]=distanceASCII;
			disp[12]="cm";
			disp[16]="tourner droite";
			_delay_ms(50);
		}
    }
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