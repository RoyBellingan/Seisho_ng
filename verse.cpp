#include "verse.h"

verse::verse()
{
    g=globalish::getInstance ();
}


verse_coord verse::id_verse2coord (int id_verse){

    versetto.id_verse=id_verse;
    QSqlQuery query(g->db_common);
    str.clear ();
    str.append ("select book,chapter,verse from verse where id_verse = " + id_verse);
    query.exec(str.toAscii ());
    query.next ();
    QVariant val =  query.value(0);
    versetto.book=val.toInt ();
    val =  query.value(1);
    versetto.chapter=val.toInt ();
    val =  query.value(2);
    versetto.verse=val.toInt ();

}

int verse::coord2id_verse (int book, int chapter, int verse){
    versetto.book=book;
    versetto.chapter=chapter;
    versetto.verse=verse;
    QSqlQuery query(g->db_common);
    str.clear ();
    str.append ("select id_verse from verse where book = ");
    str.append (QString::number(book));
    str.append (" and chapter = ");
    str.append (QString::number(chapter));
    str.append (" and verse = ");
    str.append (QString::number(verse));

    query.exec(str.toAscii ());
    query.next ();
    QVariant val =  query.value(0);
    versetto.id_verse=val.toInt ();

    return versetto.id_verse;
}


int verse::chapter_count (int book){

    str.clear ();
    str.append ("select count(chapter) from verse where book = ");
    str.append (QString::number(book));
    str.append (" AND verse =1");
    QSqlQuery query(g->db_common);
    query.exec(str.toAscii ());
    query.next ();
    QVariant val =  query.value(0);

    int cc = val.toInt();
    return cc;
}

QString verse::book_name (int book){
    str.clear ();
    str.append ("select name from book_name where id_book = ");
    str.append (QString::number(book));
    QSqlQuery query(g->db_lang1);
    query.exec(str.toAscii ());
    query.next ();
    QVariant val =  query.value(0);

    return val.toString ();
}

QString verse::chapter_r1(int book, int chapter){

    int v_init, v_end;
    QVariant val;

    v_init=coord2id_verse (book,chapter,1) - 1;
    v_end=coord2id_verse (book,chapter+1,1)-1-v_init;
    str.clear ();
    str.append ("select text from text where id_verse > ");
    str.append (QString::number(v_init));
    str.append (" limit ");
    str.append (QString::number(v_end));
    //qDebug (str.toAscii ());
    QSqlQuery query(g->db_lang1);
    query.exec(str.toAscii ());


    int i=1;
    str.clear ();

    str.append ("<div id=\"bla\">");
    while (query.next ()){
        str2.clear();
        val =  query.value(0);

        str.append ("<br>");
        str.append(QString::number(i));
        str.append ("<br>");
        str2.append (val.toString ());
        str2.replace (QString(" "), QString("  "));
        str.append (str2);
        str.append ("");
        i++;

    }

    str.replace (QString("\\n"),QString("<br>"));
    str.append("</div>");

    return str;
}
