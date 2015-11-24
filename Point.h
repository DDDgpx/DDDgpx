#ifndef POINT_H
#define POINT_H


  /*! \class Point
   * \brief La classe Point du projet
   *
   *  La classe représente un point dans l'espace repéré par un identifiant unique et des coordonnées 3D exprimées au meme système du MNT
   */
class Point
{
public:
 /*!
     *  \brief Constructeur 
	 *
     *Constructeur par défaut de la classe Point 
	 *
     */
    Point();//Par defaut (normalement pas utilisé)
	 /*!
     *  \brief Constructeur par copie 
	 *
     *Constructeur par copie de la classe Point 
	 *
     */
    Point(Point const&);//De copie
	 /*!
     *  \brief Constructeur 
	 *
     *Constructeur un point en conaissant ses coordonnées
	 *
     */
	
    Point(float x, float y, float z);//Avec paramètres
    int id_point; /*!< L'identifiant unique du point */
    float x; /*!< La composante selon l'axe X du point */
    float y;/*!< La composante selon l'axe Y du point */
    float z;/*!< La composante selon l'axe Z du point */
  //Getters
    float getX(void) const ;
    float getY(void) const ;
    float getZ(void) const ;
  //Setters
    void setX(float);
    void setY(float);
    void setZ(float);
private:


};

#endif // POINT_H
