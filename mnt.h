#ifndef MNT_H
#define MNT_H
#define TAILLE_MAX 1024
/*!
 * \file mnt.h
 * \brief Modèle numérique de terrain
 * \author ELJABIRI, MILVILLE
 * \version 1.0
 */
#include "Point.h"
#include "dalle.h"
#include "triangle.h"
#include<iostream>
#include <vector>
#include <QGLViewer/qglviewer.h>

  /*! \class Mnt
   * \brief classe representant le modèle numérique de terrain
   *
   *  La classe represente un fchier MNT et toutes ses proprietés 
   */
class Mnt
{
public:
 /*!
     *  \brief Constructeur 
	 *
     *Constructeur de la classe MNT
	 *
     */
    Mnt();
	 /*!
     *  \brief Chargement d'un MNT
     *
     *  Methode qui permet de charger un MNT
     *
     *  \param fileName : le chemin absolu du fichier MNT
     *
     */
    void loadMnt(std::string fileName);
	 /*!
     *  \brief Triangulation
     *
     *  Methode qui permet de construire les triangles d'un MNT
     *
     *  
     *
     */
    void BuildTriangles();
	 /*!
     *  \brief initialisation des limites du MNT
     *
     *  Methode qui permet d'initialiser les bornes min et max du mnt
     *
     *  
     *
     */
    void initializBounding();

    /*******/
    std::vector<Point> lesPoints ; /*!< Vecteur des points du mnt ordonné dans le sens de lecture du fichier mnt */
    std::vector<Triangle> lesTriangles ; /*!< Vecteur des triangles du mnt construits à partir du vecteur de points */
    qglviewer::Vec MIN_MNT; /*!< vecteur 3d rassemblant les valeurs min en X, Y et Z du MNT */
    qglviewer::Vec MAX_MNT;  /*!< vecteur 3d rassemblant les valeurs max en X, Y et Z du MNT */
    float pasX;  /*!< Le pas en metre selon l'axe X de la grille Mnt*/
    float pasY;  /*!< Le pas en metre selon l'axe Y de la grille Mnt*/
    int nC; /*!< Le nombre de colonnes de la grille*/
    int nL; /*!< Le nombre de lignes de la grille*/
	bool isDisplayed=false;  /*!< variable stockant l'état d'affichage du MNT*/

    
   



};

#endif // MNT_H
