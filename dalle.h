#ifndef DALLE_H
#define DALLE_H
/*!
 * \file dalle.h
 * \brief Une emprise du MNT 
 * \author ELJABIRI, MILVILLE
 * \version 1.0
 */
#include "Point.h"
#include <vector>
#include "triangle.h"

  /*! \class Mnt
   * \brief classe représentant une emprise du MNT
   *
   *  La classe représente une emprise du MNT
   */class Dalle
{
public:
 /*!
     *  \brief Constructeur 
	 *
     *Constructeur de la classe Dalle
	 *
     */
    Dalle();

    Point debut; /*!< Le point de début de la dalle dans le sens de la construction de la grille. Attention ce n'est pas la borne min de la dalle*/
    Point fin; /*!< Le dernier point de la dalle dans le sens de la construction de la grille. Attention ce n'est pas la borne max de la dalle*/
    std::vector<int> id_sesPoints; /*!< les identifiants des points de la grille de la dalle*/ 
    std::vector<Triangle> sesTriangles ; /*!< les triangles de la dalles*/
	int nC_dalle; /*!< Le nombre de colonnes de la grille dalle*/
    int nL_dalle; /*!< Le nombre de lignes de la grille dalle*/
    float z_min; /*!< L'altitude minimale de la dalle*/
    float z_max; /*!< L'altitude maximale de la dalle*/
    float z_max_ses_triangles; /*!< La valeur max de l'altitude des triangles de la dalle*/
    float z_min_ses_triangles;  /*!< La valeur min de l'altitude des triangles de la dalle*/



    /******Méthodes*****/
   //
     void BuildTriangles();
     //void initialize_altitude(MNT & unMnt);


};

#endif // DALLE_H
