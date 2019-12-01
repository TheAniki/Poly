#ifndef SON_H
#define SON_H

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>

//do re mi fa sol la si do
enum Note // on se facilite l ecriture d une melodie avec une fonction qui prendrait une note et sa tonalite
{
    la = 45,    
    sib = 46,
    si = 47,
    d = 48,
    reb = 49,
    re = 50,
    mib = 51,
    mi = 52,
    fa = 53,
    solb = 54,
    sol= 55,
    lab = 56,  

};
         
class Son
{
private:
    
public:
    Son();    
    void note(Note note, int tonalite);    

    void GameOfThrones(); //melodie 1
    void operationFaite(); // //melodie 2
    void DejaVu();//melodie 3
    void arreterSon(); 
};


#endif // SON_H