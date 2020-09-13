#ifndef VIEW_H
#define VIEW_H

#include<QGraphicsView>

class View : public QGraphicsView
{
public:
    View(QGraphicsScene *scene) : QGraphicsView(scene) { }
protected:
    void resizeEvent(QResizeEvent *event) override
    {
        QGraphicsView::resizeEvent(event);
        //fitInView(sceneRect(), Qt::KeepAspectRatio);
        fitInView(sceneRect());
    }
};

#endif // VIEW_H

