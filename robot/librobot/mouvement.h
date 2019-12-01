#ifndef MOUVEMENT_H
#define MOUVEMENT_H

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "PWM_roue.h"

void initialisationMouvement();
void arretMouvement();
void tournerDroite45();
void tournerDroite90();
void tournerGauche45();
void tournerGauche90();
void tournerUnPeuDroite();
void tournerUnPeuGauche();
void tournerDroite();
void tournerGauche();



#endif // MOUVEMENT_H