#ifndef GPX_H
#define GPX_H
/*!
 * \file gpx.h
 * \brief Le fichier GPX
 * \author ELJABIRI, MILVILLE
 * \version 1.0
 */
#include <vector>
#include "Point.h"
#include "dalle.h"
#include <string>
#include "mnt.h"
#include <QDebug>
#include <QString>
#include <QFile>

using namespace std;
  /*! \class GPX
   * \brief classe representant le GPX 
   *
   *  La classe represente le fichier GPX contenant less informations de la randonnée
   */
class gpx
{
public:
 /*!
     *  \brief Constructeur 
	 *
     *Constructeur de la classe GPX
	 *
     */
    gpx();
		 /*!
     *  \brief Chargement d'un GPX
     *
     *  Methode qui permet de charger un GPX
     *
     *  \param fileName : le chemin absolu du fichier GPX
     *
     */
    void loadGpx(QString fileName);
		 /*!
     *  \brief Détermination du triangle contenant le point
     *
     *  Methode qui permet de trouver le triangle auquel appartient le point
     *
     *  \param unMnt : le MNT composé des triangles
	 * \param p : le point à localier
     * \return l'indice du triangle englobant le point
     */
    int dansQuelTriangle(Mnt& unMnt, Point p);
			 /*!
     *  \brief Vérification d'appartenance d'un point à un triangle
     *
     *  Methode qui permet de trouver à quel triangle appartient le point
     *
     *  \param unMnt : le MNT composé des triangles
	 * \param p : le point à localiser	 
	 * \param i : l'indice du triangle
     * \return true si le point appartient au triangle
	 *false sinon
     */
    bool estDansTriangle(Point p, Mnt& unMnt, int i);

    bool conditionDansTrianglePair(Point p, Mnt& mnt, int i);
    bool conditionDansTriangleImpair(Point p, Mnt& mnt, int i);
	
    			 /*!
     *  \brief Calcul d'intersection entre un vecteur et le MNT
     *
     *  Methode qui permet de trouver la prochaine intersection dans le sens de parcours du GPX
     *
     *  \param unMnt : le MNT composé des triangles
	 * \param p : l'origine du vecteur	 
	 * \param i : l'indice de la destination?????
     */
	void trouveInterSegment(Mnt mnt, Point a, int p);
	    			 /*!
     *  \brief Calcul d'intersection entre le GPX et le MNT
     *
     *  Methode qui permet de calculer toutes les intersections entre la trajectoire du GPX et le MNT.
	 * Elle remplie le vecteur "trajectoire" du GPX
     *
     *  \param unMnt : le MNT base d'interpolation
     */
    void inter(Mnt& mnt);
    double dist(Point a, Point b);
		    			 /*!
     *  \brief Calcul le Z des points du GPX 
     *
     *  Methode qui permet de calculer la valeur de Z en faisant une interpolation
     *
     *  \param unMnt : le MNT base d'interpolation
     */
	
    void setZGpx(Mnt& mnt);
			    			 /*!
     *  \brief Calcul le Z des points des intersections entre le GPX et le MNT 
     *
     *  Methode qui permet de calculer la valeur de Z des points intermidiaires de la trajectoires en faisant une interpolation
     *
     *  \param unMnt : le MNT base d'interpolation
     */
	
    double setZInter(Mnt& mnt, Point c, Point p1, Point p2, Point p3, int indTri);
			    			 /*!
     *  \brief Initialise les limites de la dalle associée au GPX
     *
     *  Methode qui permet d'initialiser les bornes min et max de la dalle associée au GPX
	 * Elle initialise dalle.debut et dalle.fin par les points de MNT les plus proches à l'extrémité min et max  du GPX respectivement
     *
     *  \param unMnt : la grille MNT
     */
	
	void CalculateBoundsDalle(Mnt& unMnt);
    			    			 /*!
     *  \brief Détermine les indices des points de la dalle
     *
     *  Methode qui permet trouver tous les indices des points qui constituent la grille de la dalle
     *
     *  \param unMnt : la grille MNT
     */
	
	void CalculateIndicePointsDalle(Mnt& unMnt); 
	 /*!
	     *  \brief Triangulation de la dalle
     *
     *  Methode qui permet construire les triangles de la dalle
     *
     *  \param unMnt : la grille MNT
     */
    void BuildTriangles(Mnt &unMnt);
		 /*!
	     *  \brief Randonnée
     *
     *  Methode qui permet construire la trajectoire globale
     *
     *  \param unMnt : la grille MNT
     */
    void CalculateTrajectoire(Mnt &unMnt);


    Dalle gpx_dalle; /*!< Une portion du MNT associée à l'emprise de la randonnée*/
	std::vector<Point> ptsGpx; /*!< Vecteur des points du GPX esprimés au meme SRC que les coordonnées du MNT*/
	double minlat; /*!< la valeur min de Y (Latitude convertie)*/
    double maxlat; /*!< la valeur max de Y (Latitude convertie)*/
    double minlon; /*!< la valeur min de X (Longitude convertie)*/
    double maxlon; /*!< la valeur max de X (Longitude convertie)*/
    float minZ; /*! <L'altitude min effectuée au moment de la randonnée. Calculée par interpolation*/
    float maxZ; /*! <L'altitude max effectuée au moment de la randonnée. Calculée par interpolation*/
    vector<Point> trajectoire; /*! <La trajectoire de la randonnée relative au GPX*/
    bool isDisplayed=false; /*! <Paramètre montrant l'état d'affichage de la dalle associée au GPX. Il vaut true quand la checkbox du GPX est cochée, false sinon*/
    bool textureActivated=false; /*! <Paramètre montrant si une texture est appliquée à la dalle. Il vaut true quand la checkbox Texture est cochée, false sinon*/



};

#endif // GPX_H
