#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "list.h"

class CustomQGraphicsScene;
class QGraphicsView;
class Node;
class QCloseEvent;
class View;
//class QIcon;
class QAction;
class QToolBar;
class QLabel;
class QSequentialAnimationGroup;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QIcon iconStart;
    QIcon iconStop;
    QAction *actSettings;
    QAction *actStart;
    QToolBar *toolBar;
    QLabel *lblN;

    CustomQGraphicsScene* scene;
    View* view;

    //bool quit=0;
    List *l;
    unsigned int N;                     //number of discs
    unsigned int animStep=0;            //animace celý přesun
    unsigned int animN=0;               //číslo animace
    //animN je třeba vynulovat po nastavení nového počtu disků
    int A[26],B[26],C[26];
    bool running=false;                 //běží animace?
    bool even;                          //je počet disků sudý?
    QSequentialAnimationGroup *animGroup;//skupina všech animací
    QRectF rectAnimStart;

    void setup_scene();
    void setup_actions();
    void init_fields();         //inicializuj pole s disky
    void genAnim();             //vygeneruj animace (vyřeš problém)

    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
public:
    ~MainWindow();
    MainWindow(QWidget *parent = nullptr);
    int time=1000;

    //void left(Node *uk, unsigned char tyc);
    void lr(Node *uk, unsigned char tyc);
    void down(Node *uk,unsigned char d,int (&A)[26],int (&B)[26],int (&C)[26]);//d - kde
    void up(Node *uk);

    void delay_ms(unsigned int t);
private slots:
    void settings();
    void start();
    void animstep();
    void finished();
};
#endif // MAINWINDOW_H
