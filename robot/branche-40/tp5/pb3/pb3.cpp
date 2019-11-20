#define F_CPU 8000000	
#include <avr/io.h>
#include <util/delay.h>
#include "memoire_24.h"


using namespace std;

const uint8_t ROUGE = 0x01;
const uint8_t VERTE = 0x02;
const uint8_t SORTIE = 0xFF;
const uint8_t ENTREE = 0x00;


void initialisationUART ( void ) {

// 2400 bauds. Nous vous donnons la valeur des deux

// premier registres pour vous éviter des complications

UBRR0H = 0;

UBRR0L = 0xCF;

// permettre la réception et la transmission par le UART0

UCSR0A = (1<<RXC0) | (1<<TXC0 ) ;

UCSR0B = (1<<RXEN0) | (1<<TXEN0 );

// Format des trames: 8 bits, 1 stop bits, none parity

UCSR0C = (1<<UCSZ01) | (1<< UCSZ00) ;

}
void transmissionUART ( uint8_t donnee ) {

while (!( UCSR0A & (1 << UDRE0)))  //p.174
	{};
	UDR0 = donnee;
}

int main()
{
    initialisationUART();

    Memoire24CXXX memoire; 
	uint8_t lireMemoire[0xff] = "";
	
	memoire.lecture(0x00, lireMemoire);

	 	

    return 0;
}
