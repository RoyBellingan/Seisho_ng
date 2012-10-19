#ifndef globalish_H
#define globalish_H

#include <includes.h>

/**
 * @brief The globalish class
 * @author Roy Bellingan
 *
 */
class globalish
{

private:
    static globalish* instance;

   QString str,str1,str2;

    void db_common_init();
    void load_config();
    void db_acc_init();


    QSqlDatabase db_common,db_meine, db_lang1, db_lang2;

public:
    ~globalish();

    static globalish* getInstance()
    {
        if(instance == null){
            instance = new globalish();
        }
        return instance;
    }


    void bootstrap();

    int save_config();

    QString lang1;
    QString lang2;

    int chapter_count(int book);
    QString book_name(int book);



protected:


};


#endif // globalish_H
