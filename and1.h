#ifndef AND1_H
#define AND1_H

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


#define null 0

#ifdef Q_OS_UNIX
#define PATH "static/"
#endif

#ifdef Q_OS_ANDROID
#define PATH "/mnt/sdcard/seisho_m/"
#endif





namespace Ui {
class and1;
}


class KeyPressEater : public QObject
{
    Q_OBJECT


protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

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

    //
   bool event(QEvent *event);
   //mezza risoluzione asse x
   int aresx;
   //mezza risoluzione asse y
   int aresy;

   //libro scelto
   int id_book;

   //capitolo scelto
   int id_chapter;

private slots:

    //void on_view_linkClicked(const QUrl &arg1);

    void on_main_view_linkClicked(const QUrl &arg1);

    void on_popup_view_linkClicked(const QUrl &arg1);

    void on_book_name_linkActivated(const QString &link);

    void on_homizzah_linkActivated(const QString &link);

private:
    void init_text();

    void capitolibox(QString libro);

     static and1* instance;

    // Una stringa per fare gli swap al volo ecc ecc
    QString str;

    QSqlDatabase testo;


    QFile file;
};



#endif // AND1_H
