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

#include <QUrl>


#define null 0

namespace Ui {
class and1;
}

class and1 : public QMainWindow
{
    Q_OBJECT
    
public:
    Ui::and1 *ui;
    explicit and1(QWidget *parent = 0);
    ~and1();

    static and1* getInstance()
    {
        if(instance == null){
            instance = new and1();
        }
        return instance;
    }

   // bool event(QEvent *event);
private slots:

    //void on_view_linkClicked(const QUrl &arg1);

private:
     static and1* instance;

    // Una stringa per fare gli swap al volo ecc ecc
    QString str;

    QSqlDatabase testo;




    QFile file;
};

#endif // AND1_H
