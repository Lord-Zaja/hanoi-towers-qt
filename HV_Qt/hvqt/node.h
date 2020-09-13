#ifndef NODE_H
#define NODE_H
class GraphicsRectItem;
#include<QRectF>
class Node
{
    GraphicsRectItem *obj;
    Node *next;
    unsigned int discSize;
    QRectF animRect;
public:
    friend class List;
    Node();
    Node(unsigned int discSize);
    ~Node();
    unsigned int getDiscSize() const;
    GraphicsRectItem *getObj();
    QRectF getRect()const{return animRect;}
    void setRect(QRectF rect){animRect=rect;}
};

#endif // NODE_H
