#include "and1.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    and1 w;
#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.show();
#endif
    
    return a.exec();
}
