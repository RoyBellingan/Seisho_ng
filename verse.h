#ifndef VERSE_H
#define VERSE_H

#include <globalish.h>

/** LE coordinate di un versetto..
 */
struct verse_coord{

    int id_verse, chapter, book, verse;

};

class verse
{

private:
    static verse* instance;
    globalish* g;

public:
    verse();

    static verse* getInstance()
    {
        if(instance == null){
            instance = new verse();
        }
        return instance;
    }

    verse_coord versetto;
    verse_coord id_verse2coord(int id_verse);

    int coord2id_verse(int book, int chapter,int verse );
    int* coord2id_verse (int book, int chapter);



    QString str,str1,str2,str3;

    QString chapter(int book, int chapter);
    QString chapter_r1(int book, int chapter);
    QString chapter_r2(int book, int chapter);
    QString chapter_r0(int book, int chapter);

    QString chapter_text(int book, int chapter);

    int chapter_count(int book);
    QString book_name(int book);

    QStringList sl1,sl2,sl;
















};

#endif // VERSE_H
