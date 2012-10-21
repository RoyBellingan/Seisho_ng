#include "globalish.h"


void globalish::bootstrap (){

    interlinear = false;
    font_size = 18;
    single_lang_width=800;
    interlinear_width=1235;

    layout_type = "tablet";

    interlinear_layout=0;

    db_common_init ();
    load_config ();
    db_acc_init ();
}

void globalish::db_common_init (){
    db_common = QSqlDatabase::addDatabase("QSQLITE","db_common");
    str.clear ();
    str.append (PATH "common.sqlite");
    db_common.setDatabaseName(str);

    //todo metti il check
    db_common.open ();
    bool nyan = db_common.isValid ();
    QStringList zz = db_common.tables ();


}

void globalish::load_config (){

    //TODO prevedi un backup locale del file di config...
    QSqlQuery query(db_common);

    query.exec("select value from config where id_conf=1");
    query.next ();
    QVariant val =  query.value(0);
    QString acc;
    acc=val.toString ();
    lang1=acc;

    query.exec("select value from config where id_conf=2");
    query.next ();
    val =  query.value(0);
    lang2=val.toString ();

    query.exec("select value from config where id_conf=3");
    query.next ();
    val =  query.value(0);
    if (val.toString() == "1"){
    interlinear=true;
    }else{
        interlinear=false;
    }


    //TODO una cosa che in auto legge tutti i config e li imposta... senza dover fare una quwery per ognuno...

    //memento pattern here... no me ne frego rileggo da db e amen...

}

void globalish::db_acc_init (){
    //TODo se i nomi non coincidono ecc trowa un messaggio di errore con la domanda "ma lo hai messo il db nel posto giusto" ?

    db_meine =  QSqlDatabase::addDatabase("QSQLITE","db_meine");
    db_meine.setDatabaseName(PATH "db_meine.sqlite");
    db_meine.open ();
    bool nyan = db_meine.isValid ();
    QStringList zz = db_meine.tables ();

    str.clear ();
    str.append (PATH + lang1 + ".sqlite");
    db_lang1=QSqlDatabase::addDatabase("QSQLITE","db_lang1");
    db_lang1.setDatabaseName(str);
    db_lang1.open ();
    QString na = db_lang1.databaseName ();
    nyan = db_lang1.isValid ();
    zz = db_lang1.tables ();

    str.clear ();
    str.append (PATH + lang2 + ".sqlite");
    db_lang2=QSqlDatabase::addDatabase("QSQLITE","db_lang2");
    db_lang2.setDatabaseName(str);
    db_lang2.open ();
    na = db_lang2.databaseName ();
    nyan = db_lang2.isValid ();
    zz = db_lang2.tables ();

    QSqlQuery query(db_lang2);

    query.exec("select value from config where id_conf=1");
    query.next ();
    if (query.value(0).toInt() == 1){
        lang2_type=1;
    }else{
        lang2_type=0;
    }

}









int globalish::save_config (){
    return 0;
}
