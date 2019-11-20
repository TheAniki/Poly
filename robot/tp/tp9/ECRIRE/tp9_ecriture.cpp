#include "PWMDEL.h"
#include "PWM_roue.h"
#define F_CPU 8000000
#include <util/delay.h>
#include <memoire_24.h>
#include <avr/io.h>
#include "debug.h"
#include <transmissionChaineUART.h>

int main() // a commenter!
{   
    Memoire24CXXX memoire;
    TransmissionChaineUART uart; 

    memoire.init();
    uart.initialisationUART();

    uint8_t i = 0x00;
    uint8_t Octet = uart.USART_Receive();

    memoire.ecriture(i++,Octet);

    uint16_t taille = Octet<< 8; 

    Octet = uart.USART_Receive();

    taille |= Octet; 

    memoire.ecriture(i,Octet);

    for(uint8_t i =2;i<taille;i++){
        uint8_t buffer = uart.USART_Receive();
        memoire.ecriture(i,buffer);
    }
}
