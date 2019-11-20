/*
** fichier: debug.h
** Fichier utilisant la classe TransmissionChaineUART afin d'afficher les informations de deboguage
** date: 23 octobre 2019
** auteurs:
** Ouassim Ouali
** Kevin Wassef
** Alexandre Ramtoula
** Anass Laaz
**
*/
#ifndef DEBUG_H
#define DEBUG_H

#include "transmissionChaineUART.h"
#include "string.h"


TransmissionChaineUART uart;

#define DEBUG_PRINT(str) for (unsigned int i = 0; i < strlen(str); i++){uart.transmissionUART(str[i]);}
#else
#define DEBUG_PRINT(str)
do
{
} while (true);

#endif // !DEBUG_H


