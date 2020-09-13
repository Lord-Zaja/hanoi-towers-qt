#ifndef GRAPHICSRECTITEM_H
#define GRAPHICSRECTITEM_H

#include<QObject>
#include<QGraphicsRectItem>

class GraphicsRectItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(QRectF geometry READ geometry WRITE setGeometry)
public:
    explicit GraphicsRectItem(QObject *parent = nullptr)
        :QObject(parent){}//najdi a znič dítě
    QRectF geometry()const{
        return rect();
    }
    void setGeometry(const QRectF &value){
        if(rect()!=value){
            setRect(value);
            update();
        }
    }

};

#endif // GRAPHICSRECTITEM_H
