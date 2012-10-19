#ifndef INCLUDES_H
#define INCLUDES_H

#endif // INCLUDES_H

#include <iostream>
#include <string>
#include <sstream>

#include <QMainWindow>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDir>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QVariant>

#include <QUrl>
#include <QWebFrame>
#include <math.h>

#include <globalish.h>




#ifdef Q_OS_UNIX
#define PATH "static/"
#endif

#ifdef Q_OS_ANDROID
#define PATH "/mnt/storage/seisho/"
#endif

#define null 0

