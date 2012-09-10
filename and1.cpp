#include "and1.h"
#include "ui_and1.h"


and1::and1(QWidget *parent) :   QMainWindow(parent),   ui(new Ui::and1){


    //Setto l'immagine di sfondo
    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Background,*(new QBrush(*(new QPixmap(PATH "body_bg.png")))));
    setPalette(*palette);

    //E creo la UI, altrimenti non posso caricare il testo ecc...
    ui->setupUi(this);


    //Configuro UTF - 8 per tutti gli stream testuali
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));


    //Apro il file con l'html della home page
    file.setFileName(PATH "/1");

    //TODO check se il file è aperto per davvero o no
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    //Leggo il file in str
    QTextStream in(&file);
    str.append (in.readAll ());

    //Appendo una stringa per controllare che siano ok gli utf 8...
    str.append(QString::fromUtf8 ("是下記 @#[!£$%&/ #[éé+ùÆæø] ﬖﬓﬅשׁהּמּשּקּनऩझऑसॐ३ॻປຜຝນᚓᚔⰇⰆⱙΏΛΜϢϮϫᚣᚻᛓᛟᛞრ⣩❺❮❢ϭמשק  "));


    //Modifico il frame principale per delegare i link
    QWebPage *page=new QWebPage();
    ui->main_view->setPage (page);
    ui->main_view->page ()->setLinkDelegationPolicy (ui->main_view->page ()->DelegateAllLinks);

    //Ci srivo dentro la "index"
    ui->main_view->setHtml (str.toAscii ());
    file.close ();

//Configuro l'event filter
    KeyPressEater *keyPressEater = new KeyPressEater();
    ui->main_view->installEventFilter(keyPressEater);
    //ui->->installEventFilter(keyPressEater);


    //Inizio il database

    testo = QSqlDatabase::addDatabase("QSQLITE");
    testo.setDatabaseName(PATH "italiano.sqlite");

    //Non funziona!
    if(!testo.open()) {

//        ui->log->appendPlainText("KEK db owned");

    }

    QSqlQuery query(testo);
    query.exec("select libro, capitolo, versetto, italiano_text from testo where libro = 1 and capitolo = 1 limit 10");
    QSqlRecord record = query.record();
/*
    for(int i = 0; i < record.count(); i++) {
        line.append(record.fieldName(i));
    }
*/
//str.clear ();
    while(query.next()) {
        //for(int i = 0; i < record.count(); i++) {

            QVariant val =  query.value(1);
            str.append("\n<br>capitolo: ");
            str.append(val.toString ());

            val =  query.value(2);
            str.append(" Versetto: ");
            str.append(val.toString ());
            str.append("<br>");

            val =  query.value(3);

            //qDebug(val.toString ().toLatin1 ());
            //st = val.toString ();

            str.append(val.toString ());
        //}

    }
   //ui->main_view->setHtml (str.toAscii ());



}

and1::~and1()
{
    delete ui;
}


/** Se faccio click su uno dei link
 */
void and1::on_main_view_linkClicked(const QUrl &arg1)
{
    //TODO valuta una tabella di lookup ???
    //accedo al db e vedo quanti capitoli ha questo libro

    str.clear ();
    str.append ("select count(capitolo) from testo where libro = ");
    str.append (arg1.path ());
    str.append (" AND versetto =1");
    qDebug (str.toAscii ());


    QSqlQuery query(testo);
    query.exec(str.toAscii ());
    query.next ();
    QVariant val =  query.value(0);

    str.clear ();
    str.append ("<style>   #bla {color: #FFDCA8; font-family:\"Droid Sans Mono\"}   </style> <div id=\"bla\"><br>");

    int i=0;
    int sizx = 0,sizy;

    int j;
    for ( j = 1; j < val.toInt ()+1; ++j) {
        i++;
        if (i>10){
            i=1;
            str.append("<br>");

        }

        if (j<10){
            str.append("&nbsp");
        }else{
            str.append("");
        }

            str.append(QString::number(j));
            str.append("&nbsp;");
    }

    if (j<11){
        sizx=j*30-20;
    }
    if(j==11){
        sizx=310;
    }
    if(j>11){
        sizx=330;
    }

    sizy=((j/10)-1)*20+110;


    ui->popup_view->setFixedWidth (sizx);
    ui->popup_view->setFixedHeight (sizy);

    str.append ("</div>");

    ui->popup_view->setHtml (str.toAscii ());

    ui->popup_view->move (ui->main_view->width ()/2 - 150 ,ui->main_view->height ()/2 - 150 );
    ui->popup_view->show();

}









/** Se faccio click sulla FINESTRA (non il frame web) NON sui link
 */

bool and1::event(QEvent *event) {

    if (event->type() == QEvent::MouseButtonPress) {
        ui->popup_view->hide();
        return true;
    }
    return QWidget::event(event);
}


bool KeyPressEater::eventFilter(QObject *obj, QEvent *event) {

    and1* w = and1::getInstance();

    switch (event->type()) {

    case QEvent::KeyPress: {
        //QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        //qDebug("Ate key press %d", keyEvent->key());
        return true;
        break;
    }
        /*
         case QEvent::MouseButtonPress: {
         //  QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
         w->ui->hint->hide();
         qDebug("Ate mouse press!!");
         return true;
         break;
         }
         */
        //TODO meglio on release
    //case QEvent::MouseButtonPress: {
        case QEvent::MouseButtonRelease: {
        //  QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (w->ui->popup_view->isVisible()) {
            w->ui->popup_view->hide();
            //qDebug("Ate mouse press!!");
            return QObject::eventFilter(obj, event);
        } else {
            return QObject::eventFilter(obj, event);
        }
        break;
    }

    default:
        return QObject::eventFilter(obj, event);
        break;
    }

}
