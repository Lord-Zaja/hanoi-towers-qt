#include "node.h"
#include"graphicsrectitem.h"
#include<QBrush>
#include<QRectF>
Node::Node():obj(new GraphicsRectItem),next(nullptr),discSize(0),animRect(obj->rect()){}
Node::Node(unsigned int discSize):obj(new GraphicsRectItem),next(nullptr),discSize(discSize),animRect(obj->rect()){}
Node::~Node(){
    //delete next;
    next=nullptr;
    delete obj;
    obj=nullptr;
}

unsigned int Node::getDiscSize() const{
    return discSize;
}
GraphicsRectItem *Node::getObj(){
    return obj;
}
