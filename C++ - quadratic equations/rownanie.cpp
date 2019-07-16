#include <iostream>
#include "rownanie.h"

using namespace std;

Rownanie::Rownanie()
{
    //a = new int;
    //b = new int;
    //c = new int;
    //d = new int;
    
    std::vector <int> temp(4);
    m_dw = temp;
}
  
Rownanie::Rownanie(const Rownanie &obj)
{
    //int *ac = new int;
    //int *bc = new int;
    //int *cc = new int;
    //int *dc = new int;
    std::vector <int> copy;
    
    for (unsigned int i = 0; i < m_dw.size(); i++)
    copy.push_back(obj.m_dw[i]);
    
    //copy[0] = obj.m_dw[0];
    //copy[1] = obj.m_dw[1];
    //copy[2] = obj.m_dw[2];
    //copy[3] = obj.m_dw[3];
    
    //*ac = *obj.a;
    //*bc = *obj.b;
    //*cc = *obj.c;
    //*dc = *obj.d;
}


Rownanie::~Rownanie()
{   
    //delete a;
    //delete b;
    //delete c;
    //delete d;
    
    m_dw.pop_back();
    m_dw.pop_back();
    m_dw.pop_back();
    m_dw.pop_back();
}

void Rownanie::wprowadz_dane()
{
    //cin>>*a>>*b>>*c>>*d;

    int tmp = 0;
    for (unsigned int i = 0; i < m_dw.size(); i++)
    {
        cin>>tmp;
        m_dw.at(i) = tmp;
    }
        
    return;
}


void Rownanie::formatuj_rownanie()
{
	cout<<"y =";
    
	if(0 != this->m_dw[0])
	cout<<this->m_dw[0]<<"x^2";
	
	if(0 < this->m_dw[1] && 0 != this->m_dw[0])
	cout<<"+";
    
	if(0 != this->m_dw[1])
    cout<<this->m_dw[1]<<"x";
    
	if(0 < this->m_dw[2] && 0 != this->m_dw[1] || 0 < this->m_dw[2] && 0 != this->m_dw[0])
    cout<<"+";
	
	if(0 != this->m_dw[2])
    cout<< this->m_dw[2];
    
	if(0 < this->m_dw[3] && 0 != this->m_dw[2] || 0 < this->m_dw[3] && 0 != this->m_dw[1])
    cout<<"+";
	
	if(0 != this->m_dw[3])
	cout<< this->m_dw[3] <<"i";
    
    cout<<endl<<endl<<endl;
	return;
}

int Rownanie::geta()
{
    return this->m_dw[0];
}


int Rownanie::getb()
{
    return this->m_dw[1];
}



int Rownanie::getc()
{
    return this->m_dw[2];
}



int Rownanie::getd()
{
    return this->m_dw[3];
}
