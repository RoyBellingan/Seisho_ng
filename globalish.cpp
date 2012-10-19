#include "globalish.h"


void globalish::bootstrap (){
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

}


int globalish::chapter_count (int book){

    str.clear ();
    str.append ("select count(chapter) from verse where book = ");
    str.append (QString::number(book));
    str.append (" AND verse =1");
    db_common.open ();
    QSqlQuery query(db_common);
    query.exec(str.toAscii ());
    query.next ();
    QVariant val =  query.value(0);

    int cc = val.toInt();
    return cc;
}









int globalish::save_config (){
    return 0;
}
