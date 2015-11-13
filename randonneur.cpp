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
    {
        if(i==0 || (pos_.x-randonnee[i].x<=0.1  && pos_.x-randonnee[i].x>=-0.1 && pos_.y-randonnee[i].y<=0.1 && pos_.y-randonnee[i].y>=-0.1))
        { init(); return;}
        else
        {
            pos_.x=pos_.x+pasX;
            pos_.y=pos_.y+pasY;
            pos_.z=0;
            std::cout<<"***iteration "<<i<<" : "<<pos_.x<<","<<pos_.y<<std::endl;
        }

   // if(pos_.x==randonnee[i].x && pos_.y==randonnee[i].y && pos_.z==randonnee[i].z)
        // init();
    }

    /*speed_.z -= 0.05f;
  pos_ += 0.1f * speed_;

  if (pos_.z < 0.0)
    {
      speed_.z = -0.8*speed_.z;
      pos_.z = 0.0;
    }

  if (++age_ == ageMax_)
    init();*/

}

void Randonneur::draw()
{
 // glColor3f(age_/(float)ageMax_, age_/(float)ageMax_, 1.0);
  glVertex3fv(pos_);
}


void Randonneur::init()
{
    if(i<randonnee.size()-1)
    {
        if(i==0)
        {
            pos_.x = randonnee[i].x;
            pos_.y = randonnee[i].y;
            pos_.z = randonnee[i].z;
            std::cout<<"iteration "<<i<<" :" <<pos_.x<<","<<pos_.y<<std::endl;
          }


        float vitesse=0.4;
        float normX=randonnee[i+1].x-pos_.x;
        float normY=randonnee[i+1].y-pos_.y;
            //sqrt(pow(randonnee[i+1].x-pos_.x,2)+pow(randonnee[i+1].y-pos_.y,2)+pow(randonnee[i+1].z-pos_.z,2));


         if(normX==0)
            pasX=0;
         else
            pasX=(randonnee[i+1].x-pos_.x)/(fabs(normX)*vitesse);

         if(normY==0)
            pasY=0;
         else
            pasY=(randonnee[i+1].y-pos_.y)/(fabs(normY)*vitesse);

    }

 i++;
        /*float angle = 2.0 * M_PI * rand() / RAND_MAX;
        float norm  = 0.04 * rand() / RAND_MAX;
        speed_ = qglviewer::Vec(norm*cos(angle), norm*sin(angle), rand() / static_cast<float>(RAND_MAX) );
        age_ = 0;
        ageMax_ = 50 + static_cast<int>(100.0 * rand() / RAND_MAX);*/



}
