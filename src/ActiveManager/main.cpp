#include "widget.h"
#include "StageEdit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StageEdit w;




        w.show();
    return a.exec();
}
