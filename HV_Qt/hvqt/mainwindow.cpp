#include "mainwindow.h"
#include <QGraphicsView> //vykrelsení scene
#include<QDebug>
#include"customqgraphicsscene.h"
#include"node.h"
#include<QGraphicsRectItem>
#include<QEventLoop>
#include<QThread>
#include<QCloseEvent>
#include<QRectF>
#define NDEBUG
#include<QGraphicsItemAnimation>
#include<QTimeLine>
#include"view.h"
#include<QStatusBar>
#include<QAction>
#include<QToolBar>
#include"settings.h"
#include<QLabel>
#include"Algorithm.h"
#include<QPropertyAnimation>
#include"graphicsrectitem.h"
#include<QSequentialAnimationGroup>
#include<QTimer>
#include<QSettings>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QSettings config("PRC2","Tower of Hanoi");
    time=config.value("time",1000).toInt();
    N=config.value("N",3).toUInt();
    Settings s(true);
    s.setN(N);
    s.setTime(unsigned(time));
    if(s.exec()==QDialog::Accepted){
        N=s.getN();
        time=int(s.getTime());
    }else{
        QTimer::singleShot(0, this, SLOT(close())); //neběží eventloop -> jak se rozběhne hned se zavolá close
    }
    setup_scene();
    setup_actions();
    running=false;//??
}


MainWindow::~MainWindow()
{
    delete l;
}




void MainWindow::setup_scene(){

    this->statusBar()->showMessage(tr("Creating scene"));
    scene = new CustomQGraphicsScene(this);
    view = new View(scene);
    view->scene()->setSceneRect(0,0,900,600);
    view->resize(900,600);

    this->setCentralWidget(view);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate); //při MinimalViewportUpdate se updatuje pouze objekt, bez pozadí

    init_fields();    //inicializuje pole
    l=new List();
    l->start(N,A);    //do seznamu se nasází disky

    even=true;
    if(N%2)even=false;
    for(unsigned int i=N;i>=1;i--){
        view->scene()->addItem(l->find(i)->getObj());
    }
    animGroup = new QSequentialAnimationGroup(this);
    connect(animGroup,SIGNAL(currentAnimationChanged(QAbstractAnimation*)),this,SLOT(animstep()));
    connect(animGroup,SIGNAL(finished()),this,SLOT(finished()));
    this->statusBar()->showMessage(tr("Creating animations"));
    genAnim();
}

void MainWindow::setup_actions(){
    setWindowTitle(tr("Towers of Hanoi"));
    this->statusBar()->showMessage(tr("Creating actions..."));

    iconStart=QIcon::fromTheme("media-playback-start",QIcon(":/play"));
    iconStop=QIcon::fromTheme("media-playback-pause",QIcon(":/pause"));
    QIcon iconSettings=QIcon::fromTheme("preferences-system",QIcon(":/settings"));

    actSettings=new QAction(tr("&Settings"));
    actSettings->setStatusTip(tr("Change the number of discs"));
    actSettings->setToolTip(tr("Settings"));
    actSettings->setIcon(iconSettings);

    actStart=new QAction(tr("&Start"));
    actStart->setStatusTip(tr("Start/pause"));
    actStart->setToolTip(tr("Start/pause"));
    actStart->setIcon(iconStart);

    lblN=new QLabel(tr("Steps: %1/%2").arg(animStep).arg(pow(2,N)-1));

    toolBar = this->addToolBar(tr("toolBar"));
    toolBar->addAction(actSettings);
    toolBar->addAction(actStart);
    toolBar->addWidget(lblN);

    connect(actSettings,SIGNAL(triggered()),this,SLOT(settings()));
    connect(actStart,SIGNAL(triggered()),this,SLOT(start()));

    this->statusBar()->showMessage(tr("Ready.. "), 2000);
}

void MainWindow::init_fields()
{
    for (int i = 1; i <= 26; i++)
    {
        A[i] = -1;//takto ozančuji místa, kde nejsou disky
        B[i] = -1;
        C[i] = -1;
    }
    A[0] = 0;//do[0] zapisuji kolik je na dané tyči disků
    B[0] = 0;
    C[0] = 0;
}

void MainWindow::up(Node *uk)
{
#ifndef NDEBUG
    qDebug()<<"up";
#endif
    GraphicsRectItem *item=uk->getObj();
    double travelTo=90-item->rect().height();
    QRectF newRect=QRectF(uk->getRect().x(),travelTo,uk->getRect().width(),uk->getRect().height());
    QPropertyAnimation *anim=new QPropertyAnimation(item,"geometry",this);
    anim->setDuration(time);
    anim->setStartValue(uk->getRect());
    uk->setRect(newRect);
    anim->setEndValue(newRect);
    animGroup->addAnimation(anim);

}
void MainWindow::down(Node *uk,unsigned char d,int (&A)[26],int (&B)[26],int (&C)[26])
{
#ifndef NDEBUG
    qDebug()<<"down";
#endif
    double travelTo;
    GraphicsRectItem *item=uk->getObj();
    QRectF newRect;
    QPropertyAnimation *anim=new QPropertyAnimation(item,"geometry",this);
    anim->setDuration(time);
    switch (d)
    {
    case 0:
        travelTo=(590 - (item->rect().height())*(1+A[0]));
        break;
    case 1:
        travelTo=(590 - (item->rect().height())*(1+B[0]));
        break;
    case 2:
        travelTo=(590 - (item->rect().height())*(1+C[0]));
        break;
    default:
        throw tr("Down move: nonexisting position %1").arg(d);
    }
    newRect=QRectF(uk->getRect().x(),travelTo,uk->getRect().width(),uk->getRect().height());
    anim->setStartValue(uk->getRect());
    uk->setRect(newRect);
    anim->setEndValue(newRect);
    animGroup->addAnimation(anim);
}
void MainWindow::lr(Node *uk, unsigned char tyc)
{
#ifndef NDEBUG
    qDebug()<<"lr";
#endif
    GraphicsRectItem *item=uk->getObj();
    double travelTo=((150+300*tyc) - (item->rect().width() / 2));
    QRectF newRect=QRectF(travelTo,uk->getRect().y(),uk->getRect().width(),uk->getRect().height());
    QPropertyAnimation *anim=new QPropertyAnimation(item,"geometry",this);
    anim->setDuration(time);
    anim->setStartValue(uk->getRect());
    uk->setRect(newRect);
    anim->setEndValue(newRect);
    animGroup->addAnimation(anim);
}

void MainWindow::delay_ms(unsigned int t){
    QEventLoop loop;
    for(unsigned int i=0;i<=t;i++){
        if(i%2000==0)loop.processEvents(QEventLoop::AllEvents);
        QThread::msleep(1);
    }
}

void MainWindow::closeEvent(QCloseEvent *event){
    QSettings config("PRC2","Tower of Hanoi");
    config.setValue("time",time);
    config.setValue("N",N);
    event->accept();
}
void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);
#ifndef NDEBUG
    //qDebug()<<"Scale(w,h): "<<view->rect().width()/900<<" x "<<view->rect().height()/600;
#endif
}

void MainWindow::settings(){
    if(running)start();//stopni animace pokud běží
    running=false;
    Settings s;
    s.setTime(unsigned(time));
    s.setN(N);
    if(s.exec()==QDialog::Accepted){
        for(unsigned int i=N;i>=1;i--){
            view->scene()->removeItem(l->find(i)->getObj());
        }
        N=s.getN();
        time=int(s.getTime());
        animN=0;
        animStep=0;

        lblN->setText(tr("Steps: %1/%2").arg(animStep).arg(pow(2,N)-1));
        delete l;
        init_fields();
        l=new List;
        statusBar()->showMessage(tr("Writing discs to memory"));
        l->start(N,A);
        statusBar()->showMessage(tr("Putting disc to scene"));
        if(N%2){even=false;}else{even=true;}
        for(unsigned int i=N;i>=1;i--){
            view->scene()->addItem(l->find(i)->getObj());
        }
        disconnect(animGroup,SIGNAL(currentAnimationChanged(QAbstractAnimation*)),this,SLOT(animstep()));
        disconnect(animGroup,SIGNAL(finished()),this,SLOT(finished()));
        delete animGroup;
        animGroup=new QSequentialAnimationGroup(this);
        connect(animGroup,SIGNAL(currentAnimationChanged(QAbstractAnimation*)),this,SLOT(animstep()));
        connect(animGroup,SIGNAL(finished()),this,SLOT(finished()));
        genAnim();
        actStart->setEnabled(true);
    }
}

void MainWindow::start(){
    QEventLoop loop;
    if(animGroup->state()==QAbstractAnimation::Stopped&&!running){
        actStart->setIcon(iconStop);    
        running=true;
        animGroup->start();
#ifndef NDEBUG
        qDebug()<<"started";
#endif
        return;
    }
    if(animGroup->state()==QAbstractAnimation::Paused&&!running){
        actStart->setIcon(iconStop);
        running=true;
        animGroup->resume();
#ifndef NDEBUG
        qDebug()<<"resumed";
#endif
        return;
    }
    if(running&&animGroup->state()==QAbstractAnimation::Running){
        actStart->setIcon(iconStart);
        animGroup->pause();
        running=false;
#ifndef NDEBUG
        qDebug()<<"paused";
#endif
        return;
    }
}

void MainWindow::animstep(){
    animN++;
    if(animN%3==0){//pro jeden přesun disku jsou třeba tři animace
        animStep++;
        lblN->setText(tr("Steps: %1/%2").arg(animStep).arg(pow(2,N)-1));
    }
}

void MainWindow::genAnim(){
    animN=0;
    QEventLoop loop;
    this->statusBar()->showMessage(tr("Creating animations.. "));
    //ve while se vygenerují animace - spustí se hned pro zadání počtu disků, při zavolání slotu start se animce pouze spustí/pausnou
    unsigned int step=1;
    while (!(A[0]==0&&B[0]==0))//zde se věž přemístí
    {
        loop.processEvents(QEventLoop::AllEvents);
        alg(step,even,A,B,C,l,this); //upraví A,B,C - jeden krok
        step++;
    }
    this->statusBar()->showMessage(tr("Ready..."), 5000);
}

void MainWindow::finished(){
    if(animGroup->state()==QAbstractAnimation::Stopped&&running){
        actStart->setIcon(iconStart);
        actStart->setEnabled(false);
        running=false;
#ifndef NDEBUG
        qDebug()<<"finished";
#endif
    }
}
