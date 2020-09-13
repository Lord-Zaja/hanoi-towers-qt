#ifndef LIST_H
#define LIST_H

class Node;
class QRectF;
class QBrush;

class List
{
    Node *head;
    Node *current;
    unsigned char size; 
public:
    List();
    ~List();
    Node *getHead()const{return head;}
    Node *getNext(bool res=false);// res resetuje current=head
    Node *find(unsigned int discSize);
    void start(unsigned int pocet_disku,int (&start_pole)[26]);
    void newNode(unsigned int discSize,QRectF rect,QBrush brush);
};

#endif // LIST_H
