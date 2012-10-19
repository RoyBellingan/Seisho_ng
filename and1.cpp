#include "and1.h"
#include "ui_and1.h"

//https://groups.google.com/forum/?fromgroups=#!topic/android-qt/PYHwZSCZvCo per lo scroll

and1::and1(QWidget *parent) :   QMainWindow(parent),   ui(new Ui::and1){

    g=globalish::getInstance ();

    //Setto l'immagine di sfondo
    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Background,*(new QBrush(*(new QPixmap(PATH "body_bg.png")))));
    setPalette(*palette);



    //E creo la UI, altrimenti non posso caricare il testo ecc...
    ui->setupUi(this);
    ui->popup_view->hide ();
    ui->book_name->hide ();


    //Configuro UTF - 8 per tutti gli stream testuali
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));


    //Appendo una stringa per controllare che siano ok gli utf 8...
    //str.append(QString::fromUtf8 ("是下記 @#[!£$%&/ #[éé+ùÆæø] ﬖﬓﬅשׁהּמּשּקּनऩझऑसॐ३ॻປຜຝນᚓᚔⰇⰆⱙΏΛΜϢϮϫᚣᚻᛓᛟᛞრ⣩❺❮❢ϭמשק  "));


    //Modifico il frame principale per delegare i link
    QWebPage *page=new QWebPage();
   // QUrl url = QUrl("http://localhost");
   // ui->main_view->load (url);
    ui->main_view->setPage (page);
    ui->main_view->page ()->setLinkDelegationPolicy (ui->main_view->page ()->DelegateAllLinks);



    QWebPage *page2=new QWebPage();
    ui->popup_view->setPage (page2);
    ui->popup_view->page ()->setLinkDelegationPolicy (ui->main_view->page ()->DelegateAllLinks);


    //Configuro l'event filter
    KeyPressEater *keyPressEater = new KeyPressEater();
    ui->main_view->installEventFilter(keyPressEater);
    //ui->->installEventFilter(keyPressEater);


    //Intanto inizializzo la home
    init_text ();


    //Qualche static

    aresx=ui->main_view->width ()/2;
    aresy=ui->main_view->height ()/2;

}

and1::~and1()
{
    delete ui;
}


/** Se faccio click su uno dei link
 */
void and1::on_main_view_linkClicked(const QUrl &arg1)
{
capitolibox (arg1.path ());

}


//Il boxino coi capitoli
void and1::capitolibox(QString libro){

    //farewell cookies
    id_book=libro.toInt ();

    int cc=g->chapter_count (id_book);

    str.clear ();
    str.append (head);
    str.append ("<body><div id=\"bla\"><br>");

    int i=0;
    int sizx = 0,sizy;

    int j,f=0;

    if (cc>100){
        //Ma sono i salmi!
        f=1;
    }

    for ( j = 1; j < cc+1; ++j) {
        i++;
        if (i>10){
            i=1;
            str.append("<br>");
        }

        str.append("<a href=\"");
        str.append(QString::number(j));
        str.append("\">");
        if (f==1 && j < 100){
            str.append("&nbsp");
        }
        if (j<10){
            str.append("&nbsp");
        }else{
            str.append("");
        }
        str.append(QString::number(j));
        str.append("&nbsp;");
        str.append("</a>");

    }

j--;



        if (f==1){
            sizy=755;
            sizx=670;
        }else{
            sizy=(ceil((j/10)-1))*50+200;
            if (j<10){
                sizx=j*50+15;
            }
            if(j==10){
                sizx=500;
            }
            if(j>10){
                sizx=510;
            }
        }

    ui->popup_view->setFixedWidth (sizx);
    ui->popup_view->setFixedHeight (sizy);

    str.append ("</div></body>");
    //qDebug (str.toAscii ());

    ui->popup_view->setHtml (str.toAscii ());

    ui->popup_view->move (aresx - sizx/2 , aresy - sizy/2 +25 );
    ui->popup_view->show();

}

//Inizializza il testo e altre cosine
void and1::init_text(){

    //Apro il file con l'head
    file.setFileName(PATH "/1.css");

    //TODO check se il file è aperto per davvero o no
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    //Leggo il file in head ed home
    QTextStream in(&file);
    home_html.append (in.readAll ());
    head.append (home_html);
    file.close ();

    /******************************************/
    //Apro il file con l'html della home page
    file.setFileName(PATH "/1");

    //TODO check se il file è aperto per davvero o no
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    //Leggo il file in str
    QTextStream in2(&file);
    home_html.append (in.readAll ());
    file.close ();

    /******************************************/
    //Apro il file con il css di versetti
    file.setFileName(PATH "/2.css");

    //TODO check se il file è aperto per davvero o no
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    //Leggo il file in str
    QTextStream in3(&file);
    css_versetti.append (in.readAll ());
    file.close ();


    str.clear ();
    str.append ("<style> a{color: #5BB6E4; text-decoration:none} </style>  <a href=\"some\">");
    str.append("Homizzah !");
    str.append ("</a>");

    ui->homizzah->setText (str.toAscii ());

    home();

}


void and1::home(){
    //Scrivo la "index"

    ui->main_view->setHtml (home_html.toAscii ());

    //Nascondo due cosine
    ui->homizzah->hide ();
    ui->book_name->hide();

    //Forzo a non vedersi la barra di scroll
    ui->main_view->page ()->mainFrame ()->setScrollBarPolicy ( Qt::Horizontal, Qt::ScrollBarAlwaysOff);

}



/** Se faccio click sulla FINESTRA (non il frame web) NON sui link
 *nascondo il popino
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


/** Click su un link del popino, alias scelgo un capitolo da leggere
 */
void and1::on_popup_view_linkClicked(const QUrl &arg1)
{
    ui->popup_view->hide();

    str.clear ();

    str.append ("<style> a{color: #5BB6E4; text-decoration:none} </style>  <a href=\"some\">");
    str.append(g->book_name (id_book));
    str.append(" : ");
    str.append(arg1.path ());
    str.append ("</a>");
    ui->book_name->setText (str.toAscii ());
    ui->book_name->show ();

    ui->homizzah->show();

    str.clear ();
    str.append ("select italiano_text from testo where libro = ");
    str.append (QString::number(id_book));
    str.append (" and capitolo = ");
    str.append (arg1.path ());
    //qDebug (str.toAscii ());
    /*
    query.exec(str.toAscii ());

    int i=1;
    str.clear ();

    str.append (css_versetti);
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
    */
    str.replace (QString("\\n"),QString("<br>"));
    str.append("</div>");

   // qDebug (str.toAscii ());
    ui->main_view->page ()->mainFrame ()->setScrollBarPolicy ( Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    ui->main_view->setHtml (str);


}


//Faccio click sul nome di un libro
void and1::on_book_name_linkActivated(const QString &link)
{

    str.clear ();
    str.append (QString::number(id_book));
    capitolibox (str);
}

void and1::on_homizzah_linkActivated(const QString &link)
{
    home();
}
