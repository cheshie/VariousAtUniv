#include "zespolone.h"
#include <iostream>
using namespace std;

Zespolone::Zespolone()
{
    //std::vector < std::pair <float, float> > tmp(4);
    //m_complex = tmp;
}

Zespolone::~Zespolone()
{
    m_complex.pop_back();
}

float Zespolone::pomnoz(Rzeczywiste *rz, Urojone *ur, Rownanie *rw)
{
    m_complex.push_back( make_pair(rz->getx1r(),ur->getx1u()) );
    m_complex.push_back( make_pair(rz->getx2r(),ur->getx2u()) );
    m_complex.push_back( make_pair(rz->getx3r(),ur->getx3u()) );
    m_complex.push_back( make_pair(rz->getx4r(),ur->getx4u()) );
    
    if( rz->oblicz_d(rw) > 0 ) 
	{
		ur->iluset(m_complex[0].first * m_complex[1].first);
	}
	if( rz->oblicz_d(rw) < 0 )
	{
		rz->ilrset(m_complex[0].first * m_complex[1].first - m_complex[0].second * m_complex[1].second);
		ur->iluset(m_complex[0].first * m_complex[0].second + m_complex[1].first * m_complex[0].second);
	}
	if( ur->oblicz_d(rw) != 0 )
	{
        rz->ilrset((m_complex[0].first * m_complex[1].first - m_complex[0].second * m_complex[1].second)*(m_complex[2].first * m_complex[3].first - m_complex[2].second * m_complex[3].first) - (m_complex[0].first * m_complex[1].second + m_complex[1].first  * m_complex[0].second )*(m_complex[2].first  * m_complex[3].second  - m_complex[3].first  * m_complex[2].second ));
		ur->iluset((m_complex[0].first * m_complex[1].first - m_complex[0].second * m_complex[1].second)*(m_complex[2].first * m_complex[2].second + m_complex[3].first * m_complex[2].second) + (m_complex[0].first * m_complex[1].second  + m_complex[1].first  * m_complex[0].second )*(m_complex[2].first  * m_complex[3].first  - m_complex[3].second  * m_complex[2].second ));
	}
	
    m_complex.push_back( make_pair(rz->getilr(),ur->getilu()));
    
    cout<<"il: "<<m_complex[4].first<<" + "<<m_complex[4].second<<endl;
}


// void Zespolone::formatuj_lzesp(Rzeczywiste *rz, Urojone *ur)
// {
// 
//     m_complex.push_back( make_pair(rz->getx1r(),ur->getx1u()) );
//     m_complex.push_back( make_pair(rz->getx2r(),ur->getx2u()) );
//     m_complex.push_back( make_pair(rz->getx3r(),ur->getx3u()) );
//     m_complex.push_back( make_pair(rz->getx4r(),ur->getx4u()) );
//     m_complex.push_back( make_pair(rz->getilr(),ur->getilu()) );
//     
//     Printing the vector
//     for (int i=0; i<4; i++)
//     {
//         "first" and "second" are used to access
//         1st and 2nd element of pair respectively
//         cout << m_complex[i].first << " oraz "
//              << m_complex[i].second << endl;
//     }
//     
//     
//     
//     typedef struct lzespolone lz;
//     lz *liczba = new lz;
// 	
//     cout<<"\n\n Results table: \n";
//     cout<<"------------------------\n";
//     
//     if(m_complex[0].first || m_complex[0].second)
//     {
//     
//         cout<<"x1 = ";
//     
//         cout<<m_complex[0].first;
//     
//         if(m_complex[0].second > 0)
//             cout<<"+"<<m_complex[0].second<<"i";
//         else
//             cout<<m_complex[0].second;
//     
//         cout<<" |";
//         cout<<"\n------------------------\n";
//     }
//     
//     if(m_complex[1].first || m_complex[1].second)
//     {
//     
//         cout<<"x2 = ";
//     
//         cout<<m_complex[1].first;
//     
//         if(m_complex[1].second > 0)
//             cout<<"+"<<m_complex[1].second<<"i";
//         else
//             cout<<m_complex[1].second;
//     
//         cout<<" |";
//         cout<<"\n------------------------\n";
//     
//     }
//     
//     
//     if( m_complex[2].first || m_complex[2].second)
//     {
//     
//         cout<<"x3 = ";
//     
//         cout<<m_complex[2].first;
//     
//         if(m_complex[2].second > 0)
//             cout<<"+"<<m_complex[2].second<<"i";
//         else
//             cout<<m_complex[2].second;
//     
//         cout<<" |";
//         cout<<"\n------------------------\n";
//     
//     }
//     
//     if( m_complex[3].first || m_complex[3].second)
//     {
//         cout<<"x4 = ";
//     
//         cout<<m_complex[3].first;
//     
//         if(m_complex[3].second > 0)
//             cout<<"+"<<m_complex[3].second<<"i";
//         else
//             cout<<m_complex[3].second;
//     
//         cout<<" |";
//         cout<<"\n------------------------\n";
//     }
//     
//     if( m_complex[4].first || m_complex[4].second)
//     {
//         cout<<"il = ";
//     
//         cout<<m_complex[4].first;
//     
//         if(m_complex[4].second > 0)
//             cout<<"+"<<m_complex[4].second<<"i";
//         else
//             cout<<m_complex[4].second;
//     
//         cout<<" |";
//         cout<<"\n------------------------\n";
//     }
// }

void oblicz_pierwiastki(Rownanie *rw)
{
    
}
