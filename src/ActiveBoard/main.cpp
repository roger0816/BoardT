#include "widget.h"
#include <QApplication>
#include "Global.h"
#include "DialogPainter.h"
#include "ItemVideoCon.h"
#include "ItemVideo.h"
//#include <QtWebKitWidgets>
#define GLOBAL Global::Instance();


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



//    ItemVideoCon w;

//    w.show();

//      return a.exec();

//    DialogPainter p;

//    p.exec();

    GLOBAL;
    Widget w;


    if(argc>=2)
    {
        w.m_sTestModel = QString(argv[1]);
    }
      //  w.m_sTestModel = "C:/Users/chenchaowei/Documents/work/BoradT/bin/data/layer/ABC";


    //QTimer::singleShot(200,&w,SLOT(loadingLicense()));


#ifndef Q_OS_WINDOWS
    w.setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    //| Qt::WindowStaysOnTopHint
  //  w.setWindowOpacity(1);


   // w.show();

    float f = Global::Instance().m_iRealSize = 1;


    w.showFullScreen();
#else

    float f = Global::Instance().m_iRealSize = 0.5;

    QSize dSize(1080,1920);


    w.setMinimumSize(dSize*f);

    w.setMaximumSize(dSize*f);

    w.show();





#endif


    return a.exec();
}
