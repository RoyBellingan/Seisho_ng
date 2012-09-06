#include "and1.h"
#include "ui_and1.h"

and1::and1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::and1)
{

    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Background,*(new QBrush(*(new QPixmap(PATH "body_bg.png")))));
    setPalette(*palette);

    ui->setupUi(this);

    file.setFileName(PATH "1");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextStream in(&file);

    line.clear ();

    while (!in.atEnd()) {
        line = line.append (in.readLine());
    }

    ui->webView->setHtml (line.toAscii ());
    file.close ();
}

and1::~and1()
{
    delete ui;
}

