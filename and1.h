#ifndef AND1_H
#define AND1_H


#include<includes.h>
#include <globalish.h>
#include <verse.h>
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

   //Ritorna alla home
   void home();

private slots:

    //void on_view_linkClicked(const QUrl &arg1);

    void on_main_view_linkClicked(const QUrl &arg1);

    void on_popup_view_linkClicked(const QUrl &arg1);

    void on_book_name_linkActivated(const QString &link);

    void on_homizzah_linkActivated(const QString &link);

private:
    void init_text();


    void capitolibox(QString libro);

    globalish* g;
    verse* v;
    static and1* instance;

    //Il css
    QString head;

    //Il css versetti
    QString css_versetti;

    //La home
    QString home_html;

    // Una stringa per fare gli swap al volo ecc ecc
    QString str,str2;

    QSqlDatabase testo;


    QFile file;
};



#endif // AND1_H
