#include "Son.h"

Son::Son(){}
double puissance(int tonalite) //fonction de puissance qui remplace la tonalite par sa difference avec 0 au carre
{
    double puissance = 2;

    if (tonalite == 0)
    {
        puissance = 1;
    }

    else
    {
        while(tonalite > 0)
        {
            puissance *=2;
            tonalite --;
        }
   
    }  
    
    
    return puissance;
}

void Son::note(Note note,int tonalite)
{   
    double frequenceNote=0;
    double frequence[12]={110,116.5409404,123.4708253,130.8127827,138.5913155, 146.832384, 155.5634919,164.8137785,174.6141157,
          184.9972114,195.997718,207.6523488}; //on prend la premeiere gamme, correspond a notre tonalite de base

    if(tonalite < -5) //on estime que les sons produits avec de telles frequences (de tonalite inferieur a -5) sont pas utiles pour nous 
        tonalite = -5;

    if(tonalite > 3) //on estime que les sons produits avec de telles frequences (de tonalite superieur a 3) sont pas utiles pour nous
    {
        tonalite = 3;
    }        

    if(puissance(tonalite)*frequence[note-45] > 880 ){
        frequenceNote = frequence[0]*8; //si on depasse la note maximal qu on nous a fourni (880 Hz) alors on produit notre note maximal, un la bemol de frequence 880
    }

    else if(tonalite <0 )
    {
        frequenceNote = frequence[note-45]/puissance(tonalite); //calcul de la frequence selon notre gamme de base pour une tonalite inferieur a 0
    }

    else
    {
        frequenceNote = frequence[note-45]*puissance(tonalite); //calcul de la frequence selon notre gamme de base pour une tonalite superieur ou egal a 0
    }

    TCNT0=0;
    TCCR0A |= (1<<WGM01)| (1<<COM0A0)|(1<<COM0B1) ;
    TCCR0B|= (1<<CS02);
    OCR0A=(F_CPU/(2*256*frequenceNote))-1; // *2 pour avoir une meilleure gamme
}

void Son::GameOfThrones()
{
    note(sol,1);
    _delay_ms(400);
    TCCR0A &=(0 << COM0A1);

    for(int i =0 ; i<4;i++){             

        note(d,1);
        _delay_ms(400);
        TCCR0A &=(0 << COM0A1);

        note(mib,1);
        _delay_ms(200);
        TCCR0A &=(0 << COM0A1);

        note(fa,1);
        _delay_ms(200);
        TCCR0A &=(0 << COM0A1);

        note(sol,1);
        _delay_ms(400);
        TCCR0A &=(0 << COM0A1);
    }  
                
    for(int j =0 ; j<3;j++){
        
        note(d,1);
        _delay_ms(400);
        TCCR0A &=(0 << COM0A1);

        note(mi,1);
        _delay_ms(200);
        TCCR0A &=(0 << COM0A1);

        note(fa,1);
        _delay_ms(200);
        TCCR0A &=(0 << COM0A1);
            note(sol,1);
        _delay_ms(400);
        TCCR0A &=(0 << COM0A1);
    }  
   
}


void Son::operationFaite()
{
    note(fa,0);
    _delay_ms(50);
    TCCR0A &=(0 << COM0A1);

    note(sol,0);
    _delay_ms(50);
    TCCR0A &=(0 << COM0A1);
    
}
void Son::arreterSon()
{
    OCR0A=0x00;
    TCCR0A &=(0 << COM0A1);

}
void Son::DejaVu()
{
  
    note(d,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

     note(re,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);
     
     note(mib,1);
    _delay_ms(500);
     TCCR0A &=(0 << COM0A1);
    
    _delay_ms(25);

     note(mib,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

    _delay_ms(25);

     note(mib,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

     note(re,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);
    
    note(d,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

     note(sib,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

    //_delay_ms(125);
    _delay_ms(25);

     note(sib,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

    //_delay_ms(10);

    note(d,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);


    //_delay_ms(125);
    _delay_ms(50);

     note(d,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

    //  _delay_ms(25);

     note(sol,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

     //_delay_ms(10);

      note(fa,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

    //_delay_ms(10);

     note(mib,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

     //_delay_ms(10);

     note(d,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

    //  _delay_ms(10);

     note(mib,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

   //  _delay_ms(125);
   _delay_ms(25);

    note(mib,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

    //  _delay_ms(10);

     note(fa,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

      note(mib,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

  //  _delay_ms(10);

     note(fa,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

  //   _delay_ms(125);
    _delay_ms(25);

     note(fa,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

   // _delay_ms(10);

    note(sol,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

    _delay_ms(25);

    note(sol,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

   // _delay_ms(10);

     note(fa,1);
    _delay_ms(250);
     TCCR0A &=(0 << COM0A1);

}