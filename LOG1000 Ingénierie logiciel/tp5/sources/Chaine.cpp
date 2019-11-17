#include "Chaine.h"

Chaine::Chaine() : chaineName(""), chaineAddress(""), chaineCodePostal("") {}

Chaine::Chaine(string name, string code, string address) : chaineName(name), chaineCodePostal(code),
chaineAddress(address) {}


string Chaine::getChaineName()
{
	return this->chaineName; 
}

string Chaine::getChaineCodePostal() {
	return this->chaineCodePostal;
}

string Chaine::getChaineAddress() 
{
	return this->chaineAddress; 
}


void Chaine::setChaineName(string name) 
{ 
	this->chaineName = name; 
}

void Chaine::setChaineCodePostal(string code) {
	this->chaineCodePostal = code; 
}

void Chaine::setChaineAddress(string adr) { 
	this->chaineAddress = adr; 
}


void Chaine::afficher() {
	std::cout << "Chaine name : " << this->chaineName << std::endl;
	std::cout << "Chaine code postale : " << this->chaineCodePostal << std::endl;
	std::cout << "Chaine address : " << this->chaineAddress << std::endl;

}
