#include "list.h"
#include"node.h"
#include"graphicsrectitem.h"
#include<QBrush>
#include<QRectF>
#include<QDebug>
List::List()
    :head(new Node),current(head),size(0)
{
    head->next=nullptr;
}

List::~List(){
    current=head;
    while(size>0){
        current=head->next;
        delete head;
        head=current;
        size--;
    }
    delete current;
}

void List::newNode(unsigned int discSize,QRectF rect,QBrush brush){//přidá nový node na začátek
    if(size==0){
        head->discSize=discSize;
        head->obj->setRect(rect);
        head->obj->setBrush(brush);//qt objekty nelze odkazovat dál - objekty se nesmí kopírovat
        head->setRect(rect);
    }else{
        Node *n = new Node(discSize);
        n->obj->setRect(rect);
        n->setRect(rect);
        n->obj->setBrush(brush);
    n->next=head;								//nový disk se zapíše vždy na začátek listu a nahradí head
    head=n;
    }
    size++;
}

Node* List::getNext(bool res){
    if(res==true)
        current=head;
    else
        current=current->next;
    return current;
}

Node*List::find(unsigned int discSize){
    Node*pom=head;
    while (pom!= nullptr)
    {
        if (pom->discSize == discSize) { break; }//najde můj disk, který chci přesunout
        pom =pom->next;
    }
    return pom;
}

void List::start(unsigned int pocet_disku,int (&start_pole)[26]){//načtení disků do seznamu
    QRectF rect;
    QBrush brush(Qt::SolidPattern);
    rect.setHeight(500.0/pocet_disku);//výška disků je všude stejná
    unsigned int max_width=290;
    for (unsigned int i = 0; i < pocet_disku; i++){
        /*rect.setX(150-rect.width()/2);//150 - polovina první tyče
        rect.setY(590-(i+1)*(rect.height()));//dolní mezní pozice (nad trávou)
        rect.setHeight(500.0/pocet_disku);//výška disků je všude stejná
        rect.setWidth(max_width-(max_width/pocet_disku)*i);
        *///proč se sakra mění velikost rect když změním jeho pozici
        rect.setX(150-(max_width-(max_width/pocet_disku)*i)/2);     //150 - polovina první tyče
        rect.setY(591-(i+1)*((500.0/pocet_disku)));                //dolní mezní pozice (nad trávou)
        rect.setHeight(500.0/pocet_disku);                        //výška disků je všude stejná
        rect.setWidth(max_width-(max_width/pocet_disku)*i);


        brush.setColor(QColor(rand()%255,rand()%255,rand()%255));
        start_pole[i+1] = int(pocet_disku-i);		//velikost disků
        start_pole[0] = int(pocet_disku);			//počet disků v poli
        newNode(pocet_disku-i,rect,brush);   	//zapíše vše do seznamu
        //na pozici [1] v poli je největší disk
        //disky se zapisují od největšího po nejmenší
    }//vytvoří potřebný počet disků v seznamu
}
