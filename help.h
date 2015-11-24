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
  /*! \class Help
   * \brief Helper class
   *
   *  La classe contient des fonctions nécessaires pour des calculs divers
   */
class help
{
public:
	 /*!
     *  \brief conversion des coordonnées du systme WGS84 au  système des coordonnées projettées du MNT(Lambert 93)
     *
     *  Methode qui permet de convertir des coordonnées du systme WGS84 au au système des coordonnées projettées du MNT(Lambert 93)
     *
     * /param x: la longitude qui est remplacée à la sortie de la méthode par la valeur de X en coordonnées projettées 
     * /param y: la latitude qui est remplacée à la sortie de la méthode par la valeur de Y en coordonnées projettées 
     *
     */
    static void convertCoord(double &x, double &y);
		 /*!
     *  \brief Génération de fichier GPX
     *
     *  Methode qui permet de générer un fichier GPX inclus dans la zone du MNT 
     *
     * /param mnt: le MNT qui doit contenir le nouveau GPX créé
     
     *
     */
    static void creerGpx(Mnt& mnt);
		 /*!
     *  \brief conversion des coordonnées du système des coordonnées projettées du MNT(Lambert 93) ausystme WGS84 
     *
     *  Methode qui permet de convertir des coordonnées du systme des coordonnées projettées du MNT(Lambert 93) ausystme WGS84 
     *
     * /param x: la valeur de X qui est remplacée à la sortie de la méthode par la valeur de longitude en WGS84
     * /param y: la valeur de Y qui est remplacée à la sortie de la méthode par la valeur de latitude en WGS84
     *
     */
	
    static void convertInvCoord(double &x, double &y);
};

#endif // HELP_H
