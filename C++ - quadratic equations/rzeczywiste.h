#ifndef rzeczywiste_H
#define rzeczywiste_H
#include "rozwiazanie.h"
#include "urojone.h"
#include <vector>

class Rzeczywiste : public Rozwiazanie
{
protected:
    std::vector <float> m_dr;
    
    //float * x1r;
    //float * x2r;
    //float * x3r;
    //float * x4r;
    
    std::vector <float> m_rsi;
    //float * sr;
    //float * rr;
    //float * ilr;
    
public:
    Rzeczywiste();
    ~Rzeczywiste();

    float oblicz_d(Rownanie *);
    float oblicz_p_d(Rownanie *);
    float dodaj(Rownanie *);
    float odejmij(Rownanie *);
    void oblicz_pierwiastki(Rownanie *);
    void wyswietl(Rownanie *);
    void ilrset(float);
    
    float getx1r();
    float getx2r();
    float getx3r();
    float getx4r();
    float getilr();
};


#endif
