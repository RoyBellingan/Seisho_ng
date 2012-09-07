#include "and1.h"
#include <QApplication>

int main(int argc, char *argv[])
{
#if defined(Q_OS_ANDROID)
    qApp->addLibraryPath(PATH "plugins");
#endif

    QApplication a(argc, argv);
    and1 w;
#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.show();
#endif
    
    return a.exec();
}


/**
 Todo

 Aggiungi e leggi dal db sqlite

 Poi smetti android e passa a smazzarti come fare un mini seisho
 */
