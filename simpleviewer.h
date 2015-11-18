#ifndef SIMPLEVIEWER_H
#define SIMPLEVIEWER_H

#include <QGLViewer/qglviewer.h>
#include "mnt.h"
#include "gpx.h"
#include <triangle.h>
#include <randonneur.h>
#include <QOpenGLTexture>

class SimpleViewer : public QGLViewer
{

protected :
  virtual void draw();
  virtual void init();
  virtual QString helpString() const;
    void animate();
public :

    SimpleViewer();
    ~SimpleViewer();
    SimpleViewer(QWidget *parent = 0);
    Mnt *leMnt = NULL;
    gpx *leGpx = NULL;
    Randonneur *gentilhomme= NULL;
    QOpenGLTexture *textureSol;
    void loadTexture();


};

#endif
