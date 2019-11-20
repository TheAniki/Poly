#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <memoire_24.h>
#include <transmissionChaineUART.h>
#define BUTTON_IS_PRESSED PIND & 0X04
#define VERT 0X02
#define ROUGE 0x01
#define ETEINT 0x00

void initialisationUART (void) {
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la reception et la transmission par le UART0
    UCSR0A |= (1 << RXC0) | (1 << TXC0);//reception
    UCSR0B |= (1 << RXEN0)|(1 << TXEN0); //transmission
    // Format des trames: 8 bits, 1 stop bits, none parity
    UCSR0C |= (1 << UCSZ00)|(1 << UCSZ10); 
}

// De l'USART vers le PC
void transmissionUART (uint8_t donnee) {
    while (!( UCSR0A & (1 << UDRE0)))
    {};
    UDR0 = donnee;
}

void afficherChaine() {
    
    initialisationUART();
    Memoire24CXXX test;
    uint8_t chaineALire;
    unsigned j=0;
    do
    {
        test.lecture(0x00+(j*sizeof(char)),&chaineALire);
        transmissionUART (chaineALire);
        ++j;
    }while(chaineALire!=0xFF);
}
