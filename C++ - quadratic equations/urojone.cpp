#include "urojone.h"
#include <iostream>
#include <math.h>
using namespace std;

Urojone::Urojone()
{
    //this->x1u = new float;
//     this->x2u = new float;
//     this->x3u = new float;
//     this->x4u = new float;
//     
//     this->su  = new  float;
//     this->ru  = new  float;
//     this->ilu = new  float;
    
    std::vector <float> tmp(4);
    m_dr = tmp;
    
    std::vector <float> tmp2(3);
    m_rsi = tmp2;
    
    
}



Urojone::~Urojone()
{
    m_dr.pop_back();
    m_dr.pop_back();
    m_dr.pop_back();
    m_dr.pop_back();
    
    m_rsi.pop_back();
    m_rsi.pop_back();
    m_rsi.pop_back();
}


float Urojone::oblicz_d(Rownanie *rownanie)
{
    return (float)(rownanie->getb() * rownanie->getb() - 4 * rownanie->geta() * rownanie->getc());
}

void Urojone::iluset(float setter)
{
    this->m_rsi[2] = setter; 
}

float Urojone::oblicz_p_d(Rownanie *rw)
{
    Rzeczywiste *rzeczy = new Rzeczywiste;
    return sqrt((sqrt(((rzeczy->oblicz_d(rw))*(rzeczy->oblicz_d(rw))+(oblicz_d(rw))*(oblicz_d(rw))))-(oblicz_d(rw)))/2);
}

/*
float Urojone::oblicz_p_d_r(float delta_r, float delta_u)
{
   	return sqrt((sqrt(((delta_r)*(delta_r)+(delta_u)*(delta_u)))+(delta_u))/2);
}


float Urojone::oblicz_p_d_u(float delta_r, float delta_u)
{
    return sqrt((sqrt(((delta_r)*(delta_r)+(delta_u)*(delta_u)))-(delta_u)/2));    
}*/

void Urojone::oblicz_pierwiastki(Rownanie *rw)
{
    Rzeczywiste *rzdelta = new Rzeczywiste;
    
    //If it's eq.^2 without imaginary
    if( 0 != rw->geta() && 0 == rw->getd())
    {
        if ( 0 > rzdelta->oblicz_d(rw) ) 
        {
            //Calculating solutions
           //*x1r = (float)((-1) * rw->getb())  / (2*rw->geta());
           m_dr[0] = (float)((-1) * sqrt(fabs(rzdelta->oblicz_d(rw)))) / (rw->geta());
            
           //*x2r = *x1r;
           m_dr[1] = -m_dr[0];
           wyswietl(rw);
		}
    }
    if ( 0 == rw->geta() && 0 != rw->getb() && 0 != rw->getd() )
    {
        //*x1r = (float)(-1) * c / b;
        m_dr[0] = (float)(-1) * rw->getd()/ rw->getb();
         wyswietl(rw);
    }
    if ( 0 != rw->geta() && 0 != rw->getd())
    {
		Rzeczywiste *rzec = new Rzeczywiste;
        
		m_dr[0] = (float)(-rw->getb()-rzec->oblicz_p_d(rw)-oblicz_p_d(rw))/(2*rw->geta());
		
        //*x2r = (float)(-b-oblicz_p_d(rw)-uroj->oblicz_p_d(rw))/(2*rw->geta());
	    
        m_dr[1] = (float)(-rw->getb()-rzec->oblicz_p_d(rw)+oblicz_p_d(rw))/(2*rw->geta());
    
        m_dr[2] = (float)(-rw->getb()-rzec->oblicz_p_d(rw) + oblicz_p_d(rw))/(2*rw->geta());
	
        //*x4r = (float)(-b-oblicz_p_d(rw) + uroj->oblicz_p_d(rw))/(2*a);
        
        m_dr[3] =  (float)(-rw->getb()-rzec->oblicz_p_d(rw) - oblicz_p_d(rw))/(2*rw->geta());
         wyswietl(rw);
	}
}


void Urojone::wyswietl(Rownanie *rw)
{
    //If it's eq.^2 without imaginary
    if( 0 != rw->geta() && 0 == rw->getd())
    {
        Rzeczywiste *rzdelta = new Rzeczywiste;
        
		if( 0 > rzdelta->oblicz_d(rw) )
		{
            cout<<"x1u: "<<m_dr[0]<<" x2u: "<<m_dr[1]<<endl;
			
            cout<<"su: "<<m_rsi[0]<<" ru: "<<m_rsi[1]<<endl;
		}
		
	}
	if ( 0 != rw->geta() && 0 != rw->getd())
    {
        cout<<"x1u: "<<m_dr[0]<<" x2u: "<<m_dr[1]<<" x3u: "<<m_dr[2]<<" x4u: "<<m_dr[3]<<endl;
		cout<<"su: "<<m_rsi[0]<<" ru: "<<m_rsi[1]<<endl;
	}
}

float Urojone::dodaj(Rownanie *rw)
{
    Rzeczywiste *rz = new Rzeczywiste;
    
	if( rz->oblicz_d(rw) < 0 )
	{
		m_rsi[0] = m_dr[0] + m_dr[1];
	}
	if( oblicz_d(rw) != 0 )
	{
		m_rsi[0] = m_dr[0] + m_dr[1] + m_dr[2] + m_dr[3];
	}
}

float Urojone::odejmij(Rownanie *rw)
{
    Rzeczywiste *rz = new Rzeczywiste;
    
	if( rz->oblicz_d(rw) < 0 )
	{
		m_rsi[1] = m_dr[0] + m_dr[1];
	}
	if( oblicz_d(rw) != 0 )
	{
		m_rsi[1] = m_dr[0] - m_dr[1] - m_dr[2] - m_dr[3];
	}
}

float Urojone::getx1u()
{
    return m_dr[0];
}


float Urojone::getx2u()
{
    return m_dr[1];
}


float Urojone::getx3u()
{
    return m_dr[2];
}


float Urojone::getx4u()
{
    return m_dr[3];
}

float Urojone::getilu()
{
    return m_rsi[2];
}
