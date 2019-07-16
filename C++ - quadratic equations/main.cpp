#include <iostream>
#include "rownanie.h"
#include "rozwiazanie.h"
#include "rzeczywiste.h"
#include "urojone.h"
#include "zespolone.h"
using namespace std;

int main()
{
    Rownanie *rownanko = new Rownanie;
    
    Rzeczywiste * rz = new Rzeczywiste;
    Urojone     * ur = new Urojone;
    
    Rozwiazanie* rw1 = rz;
    Rozwiazanie* rw2 = ur;
    
    
    rownanko->wprowadz_dane();
    rownanko->formatuj_rownanie();
    
    
    rw1->oblicz_pierwiastki(rownanko);
    rw2->oblicz_pierwiastki(rownanko);
    
    Rzeczywiste * rz_ref = dynamic_cast<Rzeczywiste *>(rw1);
    
    Urojone     * ur_ref = dynamic_cast<Urojone *>(rw2);


    Zespolone *lzesp = new Zespolone;
    //lzesp->pomnoz(rz_ref,ur_ref,rownanko);
    //lzesp->formatuj_lzesp(rz_ref,ur_ref);     
    return 0;
}
