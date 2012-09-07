#include "and1.h"
#include "ui_and1.h"

and1::and1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::and1)
{

    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Background,*(new QBrush(*(new QPixmap(PATH "body_bg.png")))));
    setPalette(*palette);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    ui->setupUi(this);

    QString str;

    file.setFileName(PATH "italiano.sqlite");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);

       int i=1;
    //while (!in.atEnd()) {

    //}

 QDir myDir;
 myDir.cd ("/tmp");

#if defined(Q_OS_ANDROID)
    line = line.append ("<h2>android time!</h2>");
    qApp->addLibraryPath("/data/data/org.kde.necessitas.ministro/files/qt/plugins");
    myDir.cd ("/mnt");

#endif
/*
       QStringList list = myDir.entryList ();
       for (int i = 0; i < list.size(); ++i){
           line.append(list.at(i).toLocal8Bit().constData());
           line.append ("<br>\n" );
       }

       QStringList list2 = QSqlDatabase::drivers();
               for (int i = 0; i < list2.size(); ++i){
                   line.append(list2.at(i).toLocal8Bit().constData());
                   line.append ("<br>\n" );
               }




    QSqlDatabase testo = QSqlDatabase::addDatabase("QSQLITE");
    testo.setDatabaseName(PATH "italiano.sqlite");

    //Non funziona!
    if(!testo.open()) {

//        ui->log->appendPlainText("KEK db owned");
        //return -1;
    }

/*
    for (int var = 0; var < testo.tables().size (); ++var) {
        qDebug(testo.tables().at (var).toAscii ()) ;
    }
*/
    /*
    QSqlQuery query(testo);
    query.exec("select libro, capitolo, versetto, italiano_text from testo where libro = 1 and capitolo = 1 limit 10");
    QSqlRecord record = query.record();

    for(int i = 0; i < record.count(); i++) {
  //      line.append(record.fieldName(i));
    }

    while(query.next()) {
        for(int i = 0; i < record.count(); i++) {
            QVariant val =  query.value(i);

            //qDebug(val.toString ().toLatin1 ());
            //st = val.toString ();

            line.append(val.toString ());
        }

    }

*/
    str=QString::fromUtf8 ("是下記 @#[!£$%&/ #[éé+ùÆæø]");
    line.append(str);

    i++;
    line = line.append (in.readLine ());

    ui->webView->setHtml (line.toAscii ());
    file.close ();

}

and1::~and1()
{
    delete ui;
}

