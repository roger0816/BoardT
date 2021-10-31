#include "widget.h"

#include "DisplayWidget.h"
#include <QApplication>
#include "DialogSelectFile.h"
#include "DialogEditGrid.h"
#include <QFontDatabase>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CDATA;

    CCTRL;
//    QDir dir(QApplication::applicationDirPath()+"/../font");

//    QStringList list =dir.entryList(QStringList()<<"*.ttf");


//    foreach(QString sPath,list)
//    {
//        QFontDatabase::addApplicationFont(sPath);
//    }



    QFile qss(":/style.qss");

    if( qss.open(QFile::ReadOnly))
    {
        qDebug("open success");

        QString style = QLatin1String(qss.readAll());

        a.setStyleSheet(style);

        qss.close();

    }


    //    DialogSelectFile f;

    //    f.exec();

    //    return a.exec();
    //    QLocale locale = QLocale::Chinese;//指定英文显示

    //    QString st = QDateTime::currentDateTime().toString("yyyyMMdd,hh:mm:ss,dddd");

    //    qDebug()<<st;

    //    QDateTime aa;

    //    aa = QDateTime::fromString("20210515,15:34:25,星期六","yyyyMMdd,hh:mm:ss,dddd");


    //    aa.setDate(QDate::fromString("1"))

    //    for( int i =0; i<7;i++)
    //    {
    //        qDebug()<<aa.addDays(i).toString("dddd");

    //        qDebug()<<aa.addDays(i).date().dayOfWeek();

    //    }



    //    return 0;



    //    QLocale locale = QLocale::Chinese;//指定中文显示
    //    //QLocale locale = QLocale::English;//指定英文显示
    //    //QLocale locale = QLocale::Japanese;//指定日文显示

    //   qDebug()<<"AA :"<< QString(locale.toString(QDateTime::currentDateTime(),QString("dddd")));//这样获得的星期为指定的语言格式下的。此处为星期一 - 星期日

    //   qDebug()<<QDateTime::currentDateTime().toString("dddd");


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
