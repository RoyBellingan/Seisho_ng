#include "and1.h"
#include <QApplication>

and1* and1::instance=null;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    and1* w=and1::getInstance ();
    w->show();

    
    return a.exec();
}
