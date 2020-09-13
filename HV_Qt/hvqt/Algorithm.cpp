#include"Algorithm.h"
#include"node.h"
#include"list.h"
#include"mainwindow.h"
#include<exception>
#include<QMessageBox>

bool alg(unsigned int step,bool even,int (&A)[26],int (&B)[26],int (&C)[26],List *l,MainWindow *g){
    //Algoritmus na řešní h.v.
    if (step % 3 == 1)
    {
        if (even)
        {
            if (A[A[0]] <= B[B[0]])
            {
                if (!move(0, 1,l,A,B,C,g)) { move(1, 0,l,A,B,C,g); }
            }
            else
            {
                if (!move(1, 0,l,A,B,C,g)) { move(0, 1,l,A,B,C,g); }
            }
        }
        else
        {
            //cout << "A->C" << endl;
            if (A[A[0]] <= C[C[0]])
            {
                if (!move(0, 2,l,A,B,C,g)) { move(2, 0,l,A,B,C,g); }
            }
            else
            {
                if (!move(2, 0,l,A,B,C,g)) { move(0, 2,l,A,B,C,g); }
            }
        }


    }
    if (step % 3 == 2)
    {
        if (even)
        {
            if (A[A[0]] <= C[C[0]])
            {
                if (!move(0, 2,l,A,B,C,g)) { move(2, 0,l,A,B,C,g); }
            }
            else
            {
                if (!move(2, 0,l,A,B,C,g)) { move(0, 2,l,A,B,C,g); }
            }
        }
        else
        {
            //cout << "A->B" << endl;

            if (A[A[0]] <= B[B[0]])
            {
                if (!move(0, 1,l,A,B,C,g)) { move(1, 0,l,A,B,C,g); }
            }
            else
            {
                if (!move(1, 0,l,A,B,C,g)) { move(0, 1,l,A,B,C,g); }
            }
        }
    }
    if (step % 3 == 0)
    {
        //cout << "B->C" << endl;

        if (B[B[0]] <= C[C[0]])
        {
            if (!move(1, 2,l,A,B,C,g)) { move(2, 1,l,A,B,C,g); }
        }
        else
        {
            if (!move(2, 1,l,A,B,C,g)) { move(1, 2,l,A,B,C,g); }
        }
    }
    return 1;
}
bool move(unsigned char source, unsigned char destination,List *l,int (&A)[26],int (&B)[26],int (&C)[26],MainWindow *g)
{
    char buff[32];
    Node*pom=nullptr;
    switch(source)
    {
    case 0:
        if (A[0] == 0) { return 0; }//na místě žádný disk není
    try {
        if(A[A[0]]<0)throw std::invalid_argument("List::find receives negative disc size");
        pom=l->find(unsigned(A[A[0]]));//najde můj disk, který chci přesunout
    } catch (std::exception &e) {
        QMessageBox::critical(g,g->tr("Critical failure"),e.what(),QMessageBox::Close);

    }
        if (pom == nullptr) { throw g->tr("Disc ",itoa(A[A[0]],buff,3)).append(" wasnt found"); }//chyba? disk nenalezen
        g->up(pom);
        switch (destination)
        {
        case 1:
            g->lr(pom, 1);
            g->down(pom,1,A,B,C);
            A[A[0]] = -1;
            A[0] -= 1;
            B[B[0]+1] = int(pom->getDiscSize());
            B[0] += 1;
            break;
        case 2:
            g->lr(pom, 2);
            g->down(pom,2,A,B,C);
            A[A[0]] = -1;
            A[0] -= 1;
            C[C[0] + 1] = int(pom->getDiscSize());
            C[0] += 1;
            break;
        }
        break;

    case 1:
        if (B[0] == 0) { return 0; }
        try {
            if(B[B[0]]<0)throw std::invalid_argument("List::find receives negative disc size");
            pom=l->find(unsigned(B[B[0]]));//najde můj disk, který chci přesunout
        } catch (std::exception &e) {
            QMessageBox::critical(g,g->tr("Critical failure"),e.what(),QMessageBox::Close);
        }
        if (pom == nullptr) { throw g->tr("Disc ",itoa(B[B[0]],buff,3)).append(" wasnt found"); }//chyba? disk nenalezen
        g->up(pom);
        switch (destination)
        {
        case 0:
            g->lr(pom, 0);
            g->down(pom,0,A,B,C);
            A[A[0] + 1] = int(pom->getDiscSize());
            A[0] += 1;
            B[B[0]] = -1;
            B[0] -= 1;
            break;
        case 2:
            g->lr(pom, 2);
            g->down(pom,2,A,B,C);
            B[B[0]] = -1;
            B[0] -= 1;
            C[C[0] + 1] = int(pom->getDiscSize());
            C[0] += 1;
            break;
        }
        break;

    case 2:
        if (C[0] == 0) { return 0; }
        try {
            if(C[C[0]]<0)throw std::invalid_argument("List::find receives negative disc size");
            pom=l->find(unsigned(C[C[0]]));//najde můj disk, který chci přesunout
        } catch (std::exception &e) {
            QMessageBox::critical(g,g->tr("Critical failure"),e.what(),QMessageBox::Close);
        }        if (pom == nullptr) { throw g->tr("Disc ",itoa(C[C[0]],buff,3)).append(" wasnt found"); }//chyba? disk nenalezen
        g->up(pom);
        switch (destination)
        {
        case 1:
            g->lr(pom, 1);
            g->down(pom,1,A,B,C);
            C[C[0]] = -1;
            C[0] -= 1;
            B[B[0] + 1] = int(pom->getDiscSize());
            B[0] += 1;
            break;
        case 0:
            g->lr(pom, 0);
            g->down(pom,0,A,B,C);
            C[C[0]] = -1;
            C[0] -= 1;
            A[A[0] + 1] = int(pom->getDiscSize());
            A[0] += 1;
            break;
        }

        break;
    }

    return 1;
}
