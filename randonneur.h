#ifndef RANDONNEUR_H
#define RANDONNEUR_H
#include <QGLViewer/qglviewer.h>
#include "Point.h"
class Randonneur
{
public:
    Randonneur();
    void init();
    void draw();
    void bouge();
    std::vector<Point> randonnee;

   private :
     qglviewer::Vec speed_, pos_;
     int age_, ageMax_;

     int i;
};

#endif // RANDONNEUR_H
