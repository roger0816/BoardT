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


    //w1.show();
    return a.exec();
}
