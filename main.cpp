#include "and1.h"
#include <QApplication>

and1* and1::instance=null;
globalish* globalish::instance=null;
verse* verse::instance=null;
int main(int argc, char *argv[])
{

    globalish* g=globalish::getInstance ();
    g->bootstrap ();

    QApplication a(argc, argv);

    and1* w=and1::getInstance ();
    w->show();

    
    return a.exec();
}

