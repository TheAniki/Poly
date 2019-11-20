#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void initialisation();
void ajustementPWM (float vitesse1, float vitesse2);
void accelerer();
void avancerVitesseConst(float vitesse);
void reculerVitesseConst(float vitesse);
