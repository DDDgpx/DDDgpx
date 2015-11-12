#include "randonneur.h"

Randonneur::Randonneur()
{     i=0;
      //init();
}


void Randonneur::bouge()
{   float vitesse=0.1;
    float norm=sqrt(pow(randonnee[i+1].x-pos_.x,2)+pow(randonnee[i+1].y-pos_.y,2)+pow(randonnee[i+1].z-pos_.z,2));
    float dx=(randonnee[i+1].x-pos_.x)/norm*vitesse;
    float dy=(randonnee[i+1].y-pos_.y)/norm*vitesse;
    float dz=(randonnee[i+1].z-pos_.z)/norm*vitesse;

    pos_.x=pos_.x+dx;
    pos_.y=pos_.y+dy;
    pos_.z=pos_.z+dz;

    if(pos_.x==randonnee[i+1].x && pos_.y==randonnee[i+1].y && pos_.z==randonnee[i+1].z)
         init();

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
        pos_.x = randonnee[i].x;
        pos_.y = randonnee[i].y;
        pos_.z = randonnee[i].z;
        /*float angle = 2.0 * M_PI * rand() / RAND_MAX;
        float norm  = 0.04 * rand() / RAND_MAX;
        speed_ = qglviewer::Vec(norm*cos(angle), norm*sin(angle), rand() / static_cast<float>(RAND_MAX) );
        age_ = 0;
        ageMax_ = 50 + static_cast<int>(100.0 * rand() / RAND_MAX);*/
        i++;
    }
}
