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

    void keyPressEvent(QKeyEvent *e);
public :

    SimpleViewer();
    ~SimpleViewer();
    SimpleViewer(QWidget *parent = 0);
    Mnt *leMnt = NULL;
    gpx *leGpx = NULL;
    gpx *gpx_dalle_mnt =NULL;
    Randonneur *gentilhomme= NULL;
    QOpenGLTexture *textureSol;
    bool animation_allowded=false;
    bool q_pressed=false;

    void loadTexture();
    void afficheTriangleCouleur(gpx *leGpx);
    void afficheMNT();
    void afficheQuadsTexture(gpx *leGpx);
    void updateView(gpx *leGpx);


};

#endif
