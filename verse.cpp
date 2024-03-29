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
//in overload we trust
int* verse::coord2id_verse (int book, int chapter){

    QSqlQuery query(g->db_common);
    str.clear ();
    str.append ("select min(id_verse),max(id_verse) from verse where book = ");
    str.append (QString::number(book));
    str.append (" and chapter = ");
    str.append (QString::number(chapter));

    query.exec(str.toAscii ());
    query.next ();

    int* p;
    int a[2];
    p=a;
    a[0]=query.value (0).toInt ();
    a[1]=query.value (1).toInt ();

    return p;
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


QStringList verse::chapter_text(int book, int chapter){
    int v_init, v_end,delta;
    int* vv=coord2id_verse (book,chapter);
    //ID extension of this chapter
    //notice the -1 for using the > only operator
    v_init=vv[0]-1;
    v_end=vv[1];
    delta=v_end-1-v_init;

    //Get the verse text
    str.clear ();
    str.append ("select text,id_verse from bible where id_verse > ");
    str.append (QString::number(v_init));
    str.append (" limit ");
    str.append (QString::number(delta));

    QSqlQuery query_text(g->db_lang1);
    query_text.exec(str.toAscii ());


    QStringList chapter_verse;
    //chapter_verse=new QStringList();
    verse_id_ar= new int [151];
    int i=0;
    while (query_text.next ()){
        chapter_verse.append(query_text.value(0).toString());
        verse_id_ar[i]=query_text.value(1).toInt();
    }
    //Get the spacer
    str.clear ();
    sl.clear ();
    sl << "select count(id_verse_init) from spacer where id_verse_init > " << QString::number(v_init) << " and id_verse_init < " << QString::number(v_end);
    str = sl.join ("");

    QSqlQuery query_spc(g->db_common);
    query_spc.exec(str.toAscii ());
    query_spc.next ();
    int spacer_num=query_spc.value (0).toInt ();

    str.clear ();
    sl.clear ();
    sl << "select id_verse_init, id_verse_end from spacer where id_verse_init > " << QString::number(v_init) << " and id_verse_init < " << QString::number(v_end);
    str = sl.join ("");

    query_spc.exec(str.toAscii ());

    i=0;
//    spacer = new int* [spacer_num+1];
//    for (i=0; i< spacer_num+1; i++){
//        spacer[i]=new int[2];
//    }

//    i=0;
//    while (query_spc.next ()){

//        spacer[i][0]=query_spc.value (0).toInt ();
//        spacer[i][1]=query_spc.value (1).toInt ();
//        i++;
//    }


    //spacer[i][1]=160; //altrimenti non prende l'ultimo spacer
    query_spc.~QSqlQuery();

    return chapter_verse;
}


QString verse::chapter_r1(int book, int chapter){

    QStringList chapter_verse = chapter_text (book,chapter);
    int i=0;
    int j=0,k=0;
    int verse_id;
    str.clear ();
    //style=\"width:1200px\"
    str.append ("<div id=\"bla\" >");
    //for each verse extracted
    str.append("<p>\n"); //inizio SICURAMENTE un nuovo paragrafo
    for (int i = 0; i < chapter_verse.size(); ++i){
        k=i+1;
        verse_id=verse_id_ar[i];
        // id=\"id_a_cap\"
        str.append ("<span class=\"cpp\" >"); //lo span che identifica il numero_versetto
        str.append (QString::number(k));
        str.append ("</span>\n");

        str2.clear();

        str2.append (chapter_verse.at(i));
        str2.replace (QString(" "), QString("  "));

        str.append ("<span class=\"ver\">\n");

        str.append (str2); //qui il coso per mettere il text_hyper per la concordanza
        str.append ("</span>\n");

//        if (spacer[j][1]==verse_id){ //se sono alla fine di un paragrafo
//            str.append("</p>\n<p>\n");
//            j++;
//        }

    }
    str.append ("</p>\n");
    str.append("</div>");

    // qDebug (str.toAscii ());
    return str;
}


QString verse::chapter_r2(int book, int chapter){

    chapter_text (book,chapter);

    int i=0;
    int j=0;
    int verse_id;
    str.clear ();
    //style=\"width:1200px\"
    str.append ("<div id=\"bla\" style=\"width:1160px\">");
    //for each verse extracted
    str.append("<p>\n"); //inizio SICURAMENTE un nuovo paragrafo
    /*while (query_text->next ()){

        i++; //il numero di versetto
        verse_id=query_text->value(1).toInt ();
        // id=\"id_a_cap\"
        str.append ("<span class=\"cpp\" >"); //lo span che identifica il numero_versetto
        str.append (QString::number(i));
        str.append ("</span>\n");

        str2.clear();
        str2.append (query_text->value(0).toString ());
        str2.replace (QString(" "), QString("  "));

        str.append ("<span class=\"ver\">\n");

        str.append (str2); //qui il coso per mettere il text_hyper per la concordanza
        str.append ("</span>\n");

        if (spacer[j][1]==verse_id){ //se sono alla fine di un paragrafo
            str.append("</p>\n<p>\n");
            j++;
        }

    }*/
    str.append ("</p>\n");
    str.append("</div>");

    // qDebug (str.toAscii ());
    return str;
}

/** I'm using a "modificable language" such as side note or a translation work"
 */
QString verse::chapter_r0(int book, int chapter){
    QStringList chapter_verse=chapter_text (book,chapter);


    int i=0;
    int j=0,k=0;
    int verse_id;
    str.clear ();
    //style=\"width:1200px\"
    str.append ("<div id=\"bla\" style=\"width:" + QString::number(g->interlinear_width) + "px\">");
    //for each verse extracted
    str.append("<p>\n"); //inizio SICURAMENTE un nuovo paragrafo
    for (int i = 0; i < chapter_verse.size(); ++i){
        k=i+1;
        verse_id=verse_id_ar[i];
        // id=\"id_a_cap\"
        str.append ("<span class=\"cpp\" >"); //lo span che identifica il numero_versetto
        str.append (QString::number(k));
        str.append ("</span>\n");

        str.append ("<span class=\"ver\">\n");


      //  str2.clear();

      //  str2.append ();
        //str2.replace (QString(" "), QString("  "));

        str.append (chapter_verse.at(i)); //qui il coso per mettere il text_hyper per la concordanza
        str.append ("</span>\n");

//        if (spacer[j][1]==verse_id){ //se sono alla fine di un paragrafo
//            str.append("</p>\n<p>\n");
//            j++;
//        }

    }
    str.append ("</p>\n");
    str.append("</div>");

    //delete spacer;
    //delete chapter_verse;
    // qDebug (str.toAscii ());
    return str;
}



QString verse::chapter(int book, int chapter){

    QString chap;
    //oh yeah!
    if (g->interlinear == true){
        if (g->lang2_type == 1){ //comment
            chap = chapter_r0 (book, chapter);
        }else{
            chap = chapter_r2 (book, chapter);
        }

    }else{
        chap = chapter_r1 (book, chapter);
    }


    return chap;

}
