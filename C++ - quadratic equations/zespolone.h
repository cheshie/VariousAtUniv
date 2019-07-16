#ifndef zespolone_H
#define zespolone_H
#include "rozwiazanie.h"
#include "rzeczywiste.h"
#include "urojone.h"
#include "lzesp.h"
#include <vector>

class Zespolone
{
private:
    std::vector < std::pair <float, float> > m_complex;

public:
    
    Zespolone();
    ~Zespolone();
    
    float pomnoz(Rzeczywiste *, Urojone *, Rownanie *);
    //void  formatuj_lzesp(Rzeczywiste *, Urojone *);
    void  oblicz_pierwiastki();
    
};


#endif
