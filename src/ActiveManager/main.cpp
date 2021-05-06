#include "widget.h"
#include "StageEdit.h"
#include "DisplayWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Widget w;


    //StageEdit w1;

    w.show();



//    QString s="AAAAAAAAAAA";

//    for(int i=0;i<10;i++)
//    {

//        s+="AA";
//        QLabel *lb=new QLabel;

//        lb->move(100,100*i);
//    lb->setText(s);

//    QSizePolicy sizes(QSizePolicy::Fixed,QSizePolicy::Fixed);

//    lb->adjustSize();

//    lb->setSizePolicy(sizes);

//    lb->show();

//    qDebug()<<lb->size();


//    }

    //w1.show();
    return a.exec();
}
