#ifndef GPX_H
#define GPX_H

#include <vector>
#include "Point.h"
#include "dalle.h"
#include <string>
#include "mnt.h"


using namespace std;

class gpx
{
public:
    gpx();
    void loadGpx(std::string fileName);

    std::vector<Point> ptsGpx;

    Triangle troisLesPlusProches(Mnt& unMnt, Point p);
    bool estDansTriangle(Point p, Mnt& unMnt, int i);
    bool conditionDansTrianglePair(Point p, Mnt& mnt, int i);
    bool conditionDansTriangleImpair(Point p, Mnt& mnt, int i);

    float minlat;
    float maxlat;
    float minlon;
    float maxlon;
    float minZ;
    float maxZ;
    vector<Point> trajectoire;
    Dalle gpx_dalle;
    void CalculateBoundsDalle(Mnt& unMnt); ////initialise dalle.debut par le point de MNT le plus proche à l'extrémité min du GPX
    void CalculateIndicePointsDalle(Mnt& unMnt); ////initialise dalle.debut par le point de MNT le plus proche à l'extrémité min du GPX
    void BuildTriangles(Mnt &unMnt);
    //
    void CalculateTrajectoire(Mnt &unMnt);

};

#endif // GPX_H
