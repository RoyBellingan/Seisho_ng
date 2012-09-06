#ifndef AND1_H
#define AND1_H

#include <QMainWindow>
#include <string>
#include <QString>
#include <QFile>
#include <QTextStream>

#define PATH "assets/"
#ifdef Q_OS_ANDROID
#define PATH "assets:"
#endif



namespace Ui {
class and1;
}

class and1 : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit and1(QWidget *parent = 0);
    ~and1();

    QString line;

    
private slots:


private:
    Ui::and1 *ui;
    QFile file;
};

#endif // AND1_H
