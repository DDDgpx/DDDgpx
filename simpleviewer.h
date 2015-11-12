#ifndef SIMPLEVIEWER_H
#define SIMPLEVIEWER_H


#include "mnt.h"
#include "gpx.h"
#include <triangle.h>
#include <randonneur.h>

class SimpleViewer : public QGLViewer
{

protected :
  virtual void draw();
  virtual void init();
  void animate();
  virtual QString helpString() const;
public :

    SimpleViewer();
    ~SimpleViewer();
    SimpleViewer(QWidget *parent = 0);
    Mnt *leMnt = NULL;
    gpx *leGpx = NULL;
    Randonneur *gentilhomme= NULL;


};

#endif
