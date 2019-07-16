#ifndef ROZWIAZANIE_H
#define ROZWIAZANIE_H
#include "rownanie.h"

class Rozwiazanie
{
    
public:
    Rozwiazanie();
    ~Rozwiazanie();
    
    virtual void  wyswietl(Rownanie *)           = 0;
    virtual void  oblicz_pierwiastki(Rownanie *) = 0;
    
    virtual float oblicz_p_d(Rownanie *)         = 0;
    virtual float oblicz_d(Rownanie *)           = 0;
    
    virtual float dodaj(Rownanie *)              = 0;
    virtual float odejmij(Rownanie *)            = 0;
};


#endif
