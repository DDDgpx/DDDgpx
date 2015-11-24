#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QMessageBox>
#include <QDebug>
#include <glwidget.h>
#include <mnt.h>
namespace Ui {
class MainWindow;
}
  /*! \class MainWindow
   * \brief La fenêtre principale du programme
   *
   *  La fenêtre principale du programme
   */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
 /*!
     *  \brief Constructeur 
	 *
     *Constructeur de la classe MainWindow 
	 *
     */
    explicit MainWindow(QWidget *parent = 0);
	 /*!
     *  \brief Destructeur 
	 *
     *Destructeur de la classe MainWindow 
	 *
     */

    ~MainWindow();
	
    QCheckBox *cbMNT ; /*!< Pointeur sur la checkbox créée dynamiquement permettant d'activer ou desactiver l'affichage du MNT   */
    QCheckBox *cbGPX ; /*!< Pointeur sur la checkbox créée dynamiquement permettant d'activer ou desactiver l'affichage de la dalle du GPX   */
    QCheckBox *cbTexture; /*!< Pointeur sur la checkbox créée dynamiquement permettant d'activer ou desactiver l'affichage d'une texture sur la dalle du GPX   */

    /*****Les méthodes******/

signals:
    void clicked();


private slots:
    void on_Action_ouvrirMNT_triggered(); /*!< Action à exécuter au moment du clique sur le menu "Ouvrir MNT"  */
    void on_actionOuvrir_GPX_triggered(); /*!< Action à exécuter au moment du clique sur le menu "Ouvrir GPX"  */
    void on_play_clicked(); /*!< Action à exécuter au moment du clique sur le  bouton "Play" pour jouer la scène et commencer l'animation  */
    void on_cbGPX_stateChanged(int arg1); /*!< Action à exécuter quand l'utilisateur change l'état de la checkbox MNT  */
    void on_cbMNT_stateChanged(int arg1); /*!< Action à exécuter quand l'utilisateur change l'état de la checkbox GPX  */
    void on_cbTexture_stateChanged(int arg1); /*!< Action à exécuter quand l'utilisateur change l'état de la checkbox Texture  */


private:
    Ui::MainWindow *ui; /*!Pointeur sur la fenetre principale  */
};

#endif // MAINWINDOW_H
