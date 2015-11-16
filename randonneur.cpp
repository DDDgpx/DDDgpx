#include "randonneur.h"
#include <math.h>
#include<iostream>

Randonneur::Randonneur()
{     i=0;
      //init();
}


void Randonneur::bouge()
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

void Randonneur::draw()
{
  glColor3f(1, 0,0);
  glVertex3fv(pos_);
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
            std::cout<<"iteration "<<i<<" :" <<pos_.x<<","<<pos_.y<<","<<pos_.z<<std::endl;
          }

    if(i<randonnee.size()-1)
    {
        float vitesse=0.5;
        float normX=randonnee[i+1].x-pos_.x;
        float normY=randonnee[i+1].y-pos_.y;
        float normZ=randonnee[i+1].z-pos_.z;

            //sqrt(pow(randonnee[i+1].x-pos_.x,2)+pow(randonnee[i+1].y-pos_.y,2)+pow(randonnee[i+1].z-pos_.z,2));


         if(normX==0)
            pasX=0;
         else
            pasX=(randonnee[i+1].x-pos_.x)/fabs(normX)*vitesse;

         if(normY==0)
            pasY=0;
         else
            pasY=(randonnee[i+1].y-pos_.y)/fabs(normY)*vitesse;
         if(normZ==0)
            pasZ=0;
         else
            pasZ=(randonnee[i+1].z-pos_.z)/fabs(normZ)*vitesse;
    }

    }

 i++;
        /*float angle = 2.0 * M_PI * rand() / RAND_MAX;
        float norm  = 0.04 * rand() / RAND_MAX;
        speed_ = qglviewer::Vec(norm*cos(angle), norm*sin(angle), rand() / static_cast<float>(RAND_MAX) );
        age_ = 0;
        ageMax_ = 50 + static_cast<int>(100.0 * rand() / RAND_MAX);*/



}
