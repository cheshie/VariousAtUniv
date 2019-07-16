#include <iostream>
#include <complex>
#include <vector>

int main()
{
    //Complex o ktorym mowilas
    //Deklaracja statyczna - z gory musimy znac rozmar
    std::complex < float > my_complex[2];
    my_complex[0] = (1.0, 2.0);
    my_complex[1] = (2.0, 3.0);

    //Pozniej dostajemy sie real i imag do czesci tego kontenera
    std::cout<<std::real(my_complex[0])<<" + "<<std::imag(my_complex[0])<<"i "<<std::endl;
    std::cout<<std::real(my_complex[1])<<" + "<<std::imag(my_complex[1])<<"i "<<std::endl;

    
    //Ja zaimplementowalem to w inny sposob: 
    //Dlaczego? Bo mechanizm jest ten sam, tylko
    //tutaj uzywasz first i second zamiast real i imag.
    //Roznica polega jednak na tym, ze w przypadku
    //takiej sklejki pair i vectora nie masz
    //do dyspozycji operatorow np. polar i norm
    //(ale za to jest push_back, ktorego complex nie posiada)
    std::vector < std::pair <float, float> >  my_complex1;
    my_complex1.push_back(std::make_pair(1.0, 2.0));
    my_complex1.push_back(std::make_pair(2.0, 3.0));
    
    //Zwroc uwage na uzycie at(0) -> on chyba punktowal ten operator
    std::cout<<my_complex1[0].first<<" + "<<my_complex1.at(0).second<<"i "<<std::endl;
    std::cout<<my_complex1[1].first<<" + "<<my_complex1[0].second<<"i "<<std::endl;

    //UWAGA: On mi w ogole nie spojrzal na te czesc programu, 
    //wiec nie wypowiem sie ktory sposob bylby bardziej "odpowiedni"
    
    return 0;
}
