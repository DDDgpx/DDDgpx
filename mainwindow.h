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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
    QCheckBox *cbMNT ;
    QCheckBox *cbGPX ;
    QCheckBox *cbTexture;

    /*****Les méthodes******/

signals:
    void clicked();


private slots:
    void on_Action_ouvrirMNT_triggered();
    void on_actionOuvrir_GPX_triggered();
    void on_play_clicked();
    void on_cbGPX_stateChanged(int arg1);
    void on_cbMNT_stateChanged(int arg1);
    void on_cbTexture_stateChanged(int arg1);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
