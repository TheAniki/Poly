#ifndef TRANSMISSIONCHAINEUART_H
#define TRANSMISSIONCHAINEUART_H

#include <avr/io.h>

class TransmissionChaineUART
{
public:
	TransmissionChaineUART() {};

	void initialisationUART(void);

	void transmissionUART(uint16_t donnee);

	void afficherChaine();

	uint8_t USART_Receive();

private:

};

#endif // !TRANSMISSIONCHAINEUART_H







