#ifndef ROWNANIE_H
#define ROWNANIE_H
#include <vector>

class Rownanie{
  
private:
    //int *a;
    //int *b;
    //int *c;
    //int *d;
    std::vector<int> m_dw;
    
public:
    Rownanie();
    Rownanie(const Rownanie&);
    ~Rownanie();
    
    void wprowadz_dane();
    void formatuj_rownanie();
    void oblicz_pierwiastki();
    
    int geta();
    int getb();
    int getc();
    int getd();
};


#endif
