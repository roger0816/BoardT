#include "widget.h"
#include "StageEdit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StageEdit w;


    CDATA.load(QApplication::applicationDirPath()+"/data/layer");

    w.show();
    return a.exec();
}
