#ifndef urojone_H
#define urojone_H
#include "rozwiazanie.h"
#include "rzeczywiste.h"

class Urojone : public Rozwiazanie
{
protected:
    //float * x1u;
    //float * x2u;
    //float * x3u;
    //float * x4u;
    std::vector <float> m_dr;
    
    //float * su;
    //float * ru;
    //float * ilu;
    std::vector <float> m_rsi;
    
public:
    Urojone();
    ~Urojone();
    
    float oblicz_d(Rownanie *);
    float oblicz_p_d(Rownanie *);
    float dodaj(Rownanie *);
    float odejmij(Rownanie *);
    float pomnoz(Rownanie *, float *, float *, float *, float *);
    void  oblicz_pierwiastki(Rownanie *);
    void  wyswietl(Rownanie *);
    void  iluset(float);
    
    float getx1u();
    float getx2u();
    float getx3u();
    float getx4u();
    float getilu();
};


#endif
