#ifndef CUSTOMQGRAPHICSSCENE_H
#define CUSTOMQGRAPHICSSCENE_H

#include <QGraphicsScene>

class CustomQGraphicsScene : public QGraphicsScene
{
public:
    int h,w;
    CustomQGraphicsScene(QObject *parent);
    ~CustomQGraphicsScene();
protected:
   void drawBackground(QPainter * painter, const QRectF & rect );
private:
   QPixmap *bgPm;
};

#endif // CUSTOMQGRAPHICSSCENE_H
