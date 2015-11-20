#ifndef HELP_H
#define HELP_H

#include "help.h"
#include <math.h>
#include <proj_api.h>
#include "mnt.h"
#include <fstream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QString>
#include <QFile>
#include <string>
#include <cstdlib>
#include <time.h>

class help
{
public:
    static void convertCoord(double &x, double &y);
    static void creerGpx(Mnt& mnt);
    static void convertInvCoord(double &x, double &y);
};

#endif // HELP_H
