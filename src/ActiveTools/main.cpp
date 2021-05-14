#include <QCoreApplication>

#include "cCmd.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cCmd cmd;


    qDebug()<<"Tools :"<<argc<<" ,  "<<argv;


    for(int i=0;i<argc;i++)
    {
        qDebug()<<i<<" : "<<argv[i];
    }

    QString sKey = "";
    QString sValue = "";

    if(argc >1)
    {

        sKey = argv[1];

       if(argc >2)
       {
           sValue = argv[2];
       }

        cmd.callCmd(sKey,sValue);

    }

    system("PAUSE");
    return 0;
   // return a.exec();
}
