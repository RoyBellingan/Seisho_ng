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

    QSqlDatabase db_common,db_meine, db_lang1, db_lang2;
    QString css_versetti;

    bool interlinear;
    int font_size;
    int single_lang_width;







protected:


};


#endif // globalish_H
