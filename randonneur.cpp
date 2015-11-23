#include "randonneur.h"
#include <math.h>
#include<iostream>

Randonneur::Randonneur()
{     i=0;
      //init();
}


void Randonneur::bouge()
{
    if(!randonnee.empty())
    {
    if(i<randonnee.size())
    {    //float dist_to_sommet_x=
        if(i==0 || (fabs(pos_.x-randonnee[i].x)<=fabs(pasX)   && fabs(pos_.y-randonnee[i].y)<=fabs(pasY) ))
        { init(); return;}
        else
        {
            pos_.x=pos_.x+pasX;
            pos_.y=pos_.y+pasY;
            pos_.z=pos_.z+pasZ;
            std::cout<<"***iteration "<<i<<" : "<<pos_.x<<","<<pos_.y<<","<<pos_.z<<std::endl;
        }

    }
    }
}

void Randonneur::draw()
{
    glColor3f(0,0,1);
    glPointSize(10.0);
    glBegin(GL_POINTS);
      glVertex3fv(pos_);
    glEnd();
}


void Randonneur::init()
{
    if(i<randonnee.size())
    {
        //if(i==0)
        {
            pos_.x = randonnee[i].x;
            pos_.y = randonnee[i].y;
            pos_.z = randonnee[i].z;
            // std::cout<<"iteration "<<i<<" :" <<pos_.x<<","<<pos_.y<<","<<pos_.z<<std::endl;

        }

        if(i<randonnee.size()-1)
        {
            float vitesse=0.3;
            float normX=randonnee[i+1].x-pos_.x;
            float normY=randonnee[i+1].y-pos_.y;
            float normZ=randonnee[i+1].z-pos_.z;

            nextSommet_.x=randonnee[i+1].x;
            nextSommet_.y=randonnee[i+1].y;
            nextSommet_.z=randonnee[i+1].z;


            if(normX==0)
                pasX=0;
            else
                pasX=(randonnee[i+1].x-pos_.x)*saVitesse;

            if(normY==0)
                pasY=0;
            else
                pasY=(randonnee[i+1].y-pos_.y)*saVitesse;
            if(normZ==0)
                pasZ=0;
            else
                pasZ=(randonnee[i+1].z-pos_.z)*saVitesse;
        }

    }

    i++;

}
