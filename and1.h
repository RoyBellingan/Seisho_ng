#ifndef AND1_H
#define AND1_H

#include <iostream>
#include <string>
#include <sstream>

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDir>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QVariant>


#ifdef Q_OS_UNIX
#define PATH "assets/"
#endif

#ifdef Q_OS_ANDROID
#define PATH "assets:/"
#endif




namespace Ui {
class and1;
}

class and1 : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit and1(QWidget *parent = 0);
    ~and1();

    QString line;

    
private slots:


private:
    Ui::and1 *ui;
    QFile file;
};

#endif // AND1_H
