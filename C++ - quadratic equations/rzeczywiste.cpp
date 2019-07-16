#include "rzeczywiste.h"
#include <iostream>
#include <math.h>
using namespace std;

Rzeczywiste::Rzeczywiste()
{
    //this->x1r = new float;
    //this->x2r = new float;
    //this->x3r = new float;
    //this->x4r = new float;
    
    //this->sr = new float;
    //this->rr = new float;
    //this->ilr = new  float;
    
    std::vector <float> tmp(4);
    m_dr = tmp;
    
    std::vector <float> tmp2(3);
    m_rsi = tmp2;
}



Rzeczywiste::~Rzeczywiste()
{
    //delete this->x1r;
    //delete this->x2r;
    //delete this->x3r;
    //delete this->x4r;
    
    //delete this->sr;
    //delete this->rr;
    //delete this->ilr;
    
    m_dr.pop_back();
    m_dr.pop_back();
    m_dr.pop_back();
    m_dr.pop_back();
    
    m_rsi.pop_back();
    m_rsi.pop_back();
    m_rsi.pop_back();
}


float Rzeczywiste::oblicz_d(Rownanie *rownanie)
{
    return (float)(rownanie->getb() * rownanie->getb() - 4 * rownanie->geta() * rownanie->getc());
}

float Rzeczywiste::oblicz_p_d(Rownanie *rw)
{
    Urojone *uroj = new Urojone;
    return sqrt((sqrt(((oblicz_d(rw))*(oblicz_d(rw))+(uroj->oblicz_d(rw))*(uroj->oblicz_d(rw))))+(uroj->oblicz_d(rw)))/2);
}

/*
float Rzeczywiste::oblicz_p_d_r(float delta_r, float delta_u)
{
   	return sqrt((sqrt(((delta_r)*(delta_r)+(delta_u)*(delta_u)))+(delta_u))/2);
}


float Rzeczywiste::oblicz_p_d_u(float delta_r, float delta_u)
{
    return sqrt((sqrt(((delta_r)*(delta_r)+(delta_u)*(delta_u)))-(delta_u)/2));    
}*/

void Rzeczywiste::oblicz_pierwiastki(Rownanie *rw)
{
    
    //If it's eq.^2 without imaginary
    if( 0 != rw->geta() && 0 == rw->getd())
    {
        
        //Calculating delta real
		if( 0 < oblicz_d(rw))
        {
            m_dr[0] = (float)(-rw->getb() -  sqrt(oblicz_d(rw)))  /(2*rw->geta());
            m_dr[1] = (float)(-rw->getb() +  sqrt(oblicz_d(rw)))  /(2*rw->geta());
             wyswietl(rw);
		}
        else if ( 0 == oblicz_d(rw))
        {
            m_dr[0] = (float)((-1) * rw->getb()) / (2*rw->geta());
            wyswietl(rw);
        }
        else if ( 0 > oblicz_d(rw) ) 
        {
            //Calculating solutions
           m_dr[0] = (float)((-1) * rw->getb())  / (2*rw->geta());
           //*x1u = (float)((-1) * sqrt(fabs(oblicz_d_r(rw)))) / (rw->geta());
            
           m_dr[1] = m_dr[0];
           //*x2u = -*x1u;
           
           wyswietl(rw);
		}
    }
    if ( 0 == rw->geta() && 0 != rw->getb() && 0 == rw->getd())
    {
        m_dr[0] = (float)-rw->getc()/rw->getb();
        wyswietl(rw);
    }
    if ( 0 == rw->geta() && 0 != rw->getb() && 0 != rw->getd() )
    {
        m_dr[0] = (float)(-1) * rw->getc() / rw->getb();
        //*x1u = (float)(-1) * d / b;
        wyswietl(rw);
    }
    if ( 0 != rw->geta() && 0 != rw->getd())
    {
		Urojone *uroj = new Urojone;
		
        m_dr[0] = (float)(-rw->getb()-oblicz_p_d(rw)-uroj->oblicz_p_d(rw))/(2*rw->geta());
		
        m_dr[1] = (float)(-rw->getb()-oblicz_p_d(rw)-uroj->oblicz_p_d(rw))/(2*rw->geta());
	    
        //*x2u = (float)(-b-oblicz_p_d_r(oblicz_d_r(a,b,c),oblicz_d_u(a,b,c,d))+oblicz_p_d_u( oblicz_d_r (a,b,c),oblicz_d_u(a,b,c,d)))/(2*a);
    
        m_dr[2] = (float)(-rw->getb()-oblicz_p_d(rw) + uroj->oblicz_p_d(rw))/(2*rw->geta());
	
        m_dr[3] = (float)(-rw->getb()-oblicz_p_d(rw) + uroj->oblicz_p_d(rw))/(2*rw->geta());
        
        //*x4u =  (float)(-b-oblicz_p_d_r(oblicz_d_r(a,b,c),oblicz_d_u(a,b,c,d)) - oblicz_p_d_u( oblicz_d_r(a,b,c),oblicz_d_u(a,b,c,d)))/(2*a);
        wyswietl(rw);
	}
}

void Rzeczywiste::wyswietl(Rownanie *rw)
{
    //If it's eq.^2 without imaginary
    if( 0 != rw->geta() && 0 == rw->getd())
    {
        //Calculating delta real
		if( 0 < oblicz_d(rw) )
        {	
            cout<<"x1r: "<<m_dr[0]<<" x2r: "<<m_dr[1]<<endl;
            cout<<"sr: "<<m_rsi[0];
		}
		else if( 0 == oblicz_d(rw) )
		{
            cout<<"x1r: "<<m_dr[0]<<endl;
		}
		else if( 0 > oblicz_d(rw) )
		{
            cout<<"x1r: "<<m_dr[0]<<" x2r: "<<m_dr[1]<<endl;
            cout<<"sr: "<<m_rsi[0]<<" rr: "<<m_rsi[1];
		}
		
	}
    if ( 0 == rw->geta() && 0 != rw->getb() && 0 == rw->getd())
    {
        cout <<"x1r: "<<m_dr[0]<< endl;
    }
    if ( 0 == rw->geta() && 0 == rw->getb() &&(0 != rw->getc() || 0 != rw->getd()))
    {
        cout<<"Układ sprzeczny. \n";
    }
    if ( 0 == rw->geta() && 0 == rw->getb() && 0 == rw->getc() && 0 == rw->getd() )
    {
        cout<<"Równanie tożsamościowe. \n";
    }
    if ( 0 == rw->geta() && 0 != rw->getb() && 0 != rw->getd() )
    {
        cout<<"x1r: "<<m_dr[0];
    }
	if ( 0 != rw->geta() && 0 != rw->getd())
    {
        cout<<"x1r: "<<m_dr[0]<<" x2r: "<<m_dr[1]<<" x3r: "<<m_dr[2]<<" x4r: "<<m_dr[3]<<endl;
        cout<<"sr: "<<m_rsi[1]<<" rr: "<<m_rsi[0]<<endl;
	}
}

void Rzeczywiste::ilrset(float setter)
{
    this->m_rsi[2] = setter;
    //*this->ilr = setter;
}

float Rzeczywiste::dodaj(Rownanie *rw)
{
    Urojone *ul = new Urojone;
    
    if( oblicz_d(rw) > 0 )
	{
		m_rsi[0] = m_dr[0] + m_dr[1];
	}
	if( oblicz_d(rw) < 0 )
	{
		//*su = *x1u + *x2u;
		m_rsi[0] = m_dr[0] + m_dr[1];
	}
	if( ul->oblicz_d(rw) != 0 )
	{
		m_rsi[0] = m_dr[0] + m_dr[1] + m_dr[2] + m_dr[3];
		//*su = *x1u + *x2u + *x3u + *x4u;
	}
}

float Rzeczywiste::odejmij(Rownanie *rw)
{
    Urojone *ul = new Urojone;
    
    if( oblicz_d(rw) > 0 )
	{
		m_rsi[1] = m_dr[0] - m_dr[1];
	}
	if( oblicz_d(rw) < 0 )
	{
		//*su = *x1u + *x2u;
		m_rsi[1] = m_dr[0] - m_dr[1];
	}
	if( ul->oblicz_d(rw) != 0 )
	{
		m_rsi[1] = m_dr[0] - m_dr[1] - m_dr[2] - m_dr[3];
		//*su = *x1u - *x2u - *x3u - *x4u;
	}
}

float Rzeczywiste::getx1r()
{
    return m_dr[0];
}


float Rzeczywiste::getx2r()
{
    return m_dr[1];
}


float Rzeczywiste::getx3r()
{
    return m_dr[2];
}


float Rzeczywiste::getx4r()
{
    return m_dr[3];
}

float Rzeczywiste::getilr()
{
    return m_rsi[2];
}
