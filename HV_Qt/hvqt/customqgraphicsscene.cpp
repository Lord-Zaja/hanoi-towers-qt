#include "customqgraphicsscene.h"
#include<QPainter>
#include<QDebug>

CustomQGraphicsScene::CustomQGraphicsScene(QObject *parent): QGraphicsScene(parent)//zničení dětí
,bgPm(new QPixmap(":/plocha.bmp"))
{
}
CustomQGraphicsScene::~CustomQGraphicsScene(){
    delete bgPm;
}

void CustomQGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
#ifndef NDEBUG
    //qDebug() << "background rect: " << rect << endl;
#endif
    h=qRound(rect.height());
    w=qRound(rect.width());
    bgPm->scaled(QSize(w, h), Qt::KeepAspectRatio);
    painter->drawPixmap(rect,*bgPm, QRect(0.0, 0.0, bgPm->width(), bgPm->height()));
}
