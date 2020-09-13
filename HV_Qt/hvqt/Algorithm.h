#ifndef ALGORITHM_H
#define ALGORITHM_H

class List;
class MainWindow;
bool alg(unsigned int step,bool even,int (&A)[26],int (&B)[26],int (&C)[26],List *l,MainWindow *g);
bool move(unsigned char source, unsigned char destination,List *l,int (&A)[26],int (&B)[26],int (&C)[26],MainWindow*g);

#endif // ALGORITHM_H
