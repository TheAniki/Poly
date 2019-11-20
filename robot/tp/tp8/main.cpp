#define F_CPU 8000000
#include <util/delay.h>
#include <string.h>
#include "debug.h"
#include "transmissionChaineUART.h"
#define SORTIE 0xFF
#define ENTREE 0x00

using namespace std;

void initialisation()
{
	DDRB = SORTIE;
	TransmissionChaineUART uart;
}

int main()
{
	initialisation();
	
	uart.initialisationUART();
	//ajouter les fonctions debug
	DEBUG_PRINT("ADLFKSDFK");
	
}