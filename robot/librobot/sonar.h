#define F_CPU 8000000
#include "PWMDEL.h"
#include "PWM_roue.h"
#include "mouvement.h"
#include <util/delay.h>
#include <avr/io.h>
//#include "debug.h"
#include "transmissionChaineUART.h"
#include <stdlib.h>
#include <stdio.h>
#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"
TransmissionChaineUART uart;
static uint16_t volatile pulse=0;

void suivreMur(bool mur);
        