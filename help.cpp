#include "help.h"

using namespace std;

void help::convertCoord(double &x, double &y){

    char *srid4326 = "+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs";
    char *srid27572 = "+proj=lcc +lat_1=46.8 +lat_0=46.8 +lon_0=0 +k_0=0.99987742 +x_0=600000 +y_0=2200000 +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +units=m +no_defs +towgs84=-168,-60,320,0,0,0,0,";

    projPJ source = pj_init_plus(srid4326);
    projPJ target = pj_init_plus(srid27572);

    x *= DEG_TO_RAD;
    y *= DEG_TO_RAD;

    pj_transform(source, target, 1, 1, &x, &y, NULL );
}
void help::convertInvCoord(double &x, double &y){

    char *srid4326 = "+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs";
    char *srid27572 = "+proj=lcc +lat_1=46.8 +lat_0=46.8 +lon_0=0 +k_0=0.99987742 +x_0=600000 +y_0=2200000 +a=6378249.2 +b=6356515 +towgs84=-168,-60,320,0,0,0,0 +pm=paris +units=m +no_defs +towgs84=-168,-60,320,0,0,0,0,";

    projPJ source = pj_init_plus(srid27572);
    projPJ target = pj_init_plus(srid4326);



    pj_transform(source, target, 1, 1, &x, &y, NULL );

    x *= RAD_TO_DEG;
    y *= RAD_TO_DEG;
}
void help::creerGpx(Mnt &mnt){
    ofstream fichier("/home/gtsi/Téléchargements/testtest.gpx", ios::trunc);
    if(fichier)
    {
        fichier << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
        fichier.close();
    }
    else
        cerr << "Erreur à l'ouverture !" << endl;

    double minlon_mnt = mnt.MIN_MNT.x;
    double minlat_mnt = mnt.MIN_MNT.y;
    double maxlon_mnt = mnt.MAX_MNT.x;
    double maxlat_mnt = mnt.MAX_MNT.y;

    convertInvCoord(minlon_mnt, minlat_mnt);
    convertInvCoord(maxlon_mnt, maxlat_mnt);

    srand(time(NULL));


    double coef = (double)(rand() % 4056)/(20*4056);
    double minlon = minlon_mnt+((49+coef)*(maxlon_mnt-minlon_mnt))/100;
    coef = (double)(rand() % 4056)/4056;
    double minlat = minlat_mnt+((49+coef)*(maxlat_mnt-minlat_mnt))/100;
    coef = (double)(rand() % 4056)/4056;
    double maxlon = minlon_mnt+((50+coef)*(maxlon_mnt-minlon_mnt))/100;
    coef = (double)(rand() % 4056)/4056;
    double maxlat = minlat_mnt+((50+coef)*(maxlat_mnt-minlat_mnt))/100;


    double lon;
    double lat;

    QString slon;
    QString slat;

    QFile file("/home/gtsi/Téléchargements/testtest.gpx");
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("gpx");

    xmlWriter.writeStartElement("metadata");
    xmlWriter.writeEmptyElement("bounds");
    xmlWriter.writeAttribute("minlat", QString::number(minlat));
    xmlWriter.writeAttribute("minlon", QString::number(minlon));
    xmlWriter.writeAttribute("maxlat", QString::number(maxlat));
    xmlWriter.writeAttribute("maxlon", QString::number(maxlon));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("trk");

    xmlWriter.writeStartElement("trkseg");

    xmlWriter.writeStartElement("trkpt");
    xmlWriter.writeAttribute("lat", QString::number(minlat));
    xmlWriter.writeAttribute("lon", QString::number(minlon));
    QString vide = "ele";
    xmlWriter.writeEmptyElement(vide);
    xmlWriter.writeEndElement();

    for (int i=0; i<20; i++){


        xmlWriter.writeStartElement("trkpt");
        coef = (double)(rand() % 4056)/4056;
        lon = minlon+((i+coef)*(maxlon-minlon))/20;
        slon = QString::number(lon);
        coef = (double)(rand() % 4056)/4056;
        lat = minlat+((i+coef)*(maxlat-minlat))/20;
        slat = QString::number(lat);
        xmlWriter.writeAttribute("lat", slat);
        xmlWriter.writeAttribute("lon", slon);
        xmlWriter.writeEmptyElement(vide);
        xmlWriter.writeEndElement();

    }
    xmlWriter.writeStartElement("trkpt");
    xmlWriter.writeAttribute("lat", QString::number(maxlat));
    xmlWriter.writeAttribute("lon", QString::number(maxlon));
    xmlWriter.writeEmptyElement(vide);
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();

    xmlWriter.writeEndDocument();

    file.close();

    cout<<"le gpx est créé"<<endl;
}
