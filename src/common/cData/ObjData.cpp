#include "ObjData.h"

ObjData::ObjData(QObject *parent) : QObject(parent)
{
    m_rect = QRect(10,10,300,180);
}

void ObjData::readData(QString sPath)
{
    m_sObjPath = sPath;

    QString sSourcePath = m_sObjPath+"/source/";

    m_sName = m_sObjPath.split("/").last();

    if(m_sObjPath.length()>1)
    {
        m_sLayerName = m_sObjPath.split("/").at(m_sObjPath.split("/").length()-2);
    }



    QSettings conf(m_sObjPath+"/conf.ini",QSettings::IniFormat);

    QString sType = m_dDefine.key(conf.value("Base/type").toInt());


    if(sType.trimmed() == "")
        return ;


    int x = conf.value("Base/x").toInt();

    int y = conf.value("Base/y").toInt();

    int w = conf.value("Base/w").toInt();

    int h = conf.value("Base/h").toInt();


    m_rect.setX(x);

    m_rect.setY(y);

    m_rect.setWidth(w);

    m_rect.setHeight(h);

    m_sType = sType;

    qDebug()<<"type "<<m_sType;

    m_dataCmd.sCmd = conf.value("Action/cmd","").toString();

    m_dataCmd.sValue1 = conf.value("Action/value1","").toString();

    m_dataCmd.sValue2 = conf.value("Action/value2","").toString();




    if(sType == E_PIC)
    {

        m_dataPic.iSec = conf.value("Pic/changeTimer",10).toInt();

        m_dataPic.listPicName =conf.value("Pic/list","").toStringList();


        QStringList listCantFind;

        for(int i=0;i<m_dataPic.listPicName.length();i++)
        {

#if 0
            QString sOriFilePath = m_dataPic.listPicName.at(i);

            QString sRootFilePath = sSourcePath+sOriFilePath.split("/").last();

            bool bHasPic = true;

            if(QFileInfo::exists(sRootFilePath))
            {
                m_dataPic.listPicName[i] = sRootFilePath;

            }
            else if(QFileInfo::exists(sOriFilePath))
            {
                QFile::copy(sOriFilePath,sRootFilePath);
            }
            else
            {
                bHasPic = false;
            }

            if(!bHasPic)
            {
                m_dataPic.listPicName.removeOne(sOriFilePath);
            }

#else

            QString sFilePath = m_dataPic.listPicName.at(i);

            if(!QFileInfo::exists(sFilePath))
            {
                sFilePath = sSourcePath+sFilePath.split("/").last();
                m_dataPic.listPicName[i] = sFilePath;
            }
            if(QFileInfo::exists(sFilePath))
            {

                //  QPixmap p(sFilePath);

                QImageReader reader(sFilePath);

                reader.setDecideFormatFromContent(true);

                m_dataPic.listPic.append(QPixmap::fromImageReader(&reader,Qt::AutoColor));
            }
            else
            {
                listCantFind.append(m_dataPic.listPicName.at(i));
            }

#endif
        }


        foreach(QString sNoFind,listCantFind)
        {
            m_dataPic.listPicName.removeOne(sNoFind);
        }


    }
    else if(sType == E_VIDEO)
    {
        // m_dataVideo.listName =conf.value("Video/list","").toStringList();


        m_dataVideo.listName.clear();

        QStringList list = conf.value("Video/list","").toStringList();

        foreach(QString sFilePath, list)
        {
            //            qDebug()<<"read: "<<sFilePath ;
            //            if(!QFileInfo(sFilePath).exists())
            sFilePath = sSourcePath+sFilePath.split("/").last();
            m_dataVideo.listName.append(sFilePath);
        }

        m_dataVideo.bIsMute =conf.value("Video/mute").toBool();

        m_dataVideo.bUseFile = conf.value("Video/userFile",true).toBool();

        m_dataVideo.sRtsp = conf.value("Video/rtsp").toString().trimmed();

    }

    else if(sType == E_GRID)
    {

        for(int i=0;i<9;i++)
        {
            QString sPathG1 = sSourcePath+QString::number(i+1);

            if(!QDir(sPathG1).exists())
                QDir().mkdir(sPathG1);

            m_dataGrid.listG1[i] = sPathG1+QString("/%1.png").arg(i+1);

            for(int j=0;j<9;j++)
            {
                QString sPathG2=sPathG1+"/"+QString::number(j+1);
                if(!QDir(sPathG2).exists())
                    QDir().mkdir(sPathG2);

                m_dataGrid.listG2[i][j]=sPathG2+QString("/%1.png").arg(j+1);

                m_dataGrid.listG3[i][j]=sPathG2+QString("/%1_d.png").arg(j+1);



            }
        }

        m_dataGrid.bHasChange = false;


        m_dataGrid.iCount = conf.value("Grid/count",9).toInt();



    }

    else if(sType == E_TXVALUE)
    {


        m_data[TxtValue::imagePath] = sSourcePath+QString("/%1.png").arg(TxtValue::imagePath);

        m_data[TxtValue::imagePathMin] = sSourcePath+QString("/%1.png").arg(TxtValue::imagePathMin);

        m_data[TxtValue::imagePathMax] = sSourcePath+QString("/%1.png").arg(TxtValue::imagePathMax);


    }

    //    else if(sType == E_BUTTON)
    //    {


    //        m_dataBtn.iType = m_data[Btn::btnType] ;

    //        m_data[Btn::btnTypeNote] = m_dataBtn.sTypeNode;

    //        m_data[Btn::btnText2] = m_dataBtn.sText2;

    //        m_data[Btn::btnInput] = m_dataBtn.sInput;

    //        m_data[Btn::btnOpuput] = m_dataBtn.sOutPut;

    //    }




    //        m_data.clear();


    conf.beginGroup("Items");
    QStringList keys = conf.childKeys();
    foreach (QString key, keys)
    {

        //  if(key!=TxtValue::imagePath && key!=TxtValue::imagePathMin && key!=TxtValue::imagePathMax)
        {
            m_data[key] = conf.value(key);

            qDebug()<<"CC : key :"<<key<<" , data : "<< m_data[key];
        }
    }


    conf.endGroup();


    qDebug()<<"read itemdata : "<<m_data;




}

void ObjData::writeData()
{

    QDir().mkdir(m_sObjPath);

    QSettings conf(m_sObjPath+"/conf.ini",QSettings::IniFormat);

    if(m_sType.trimmed() == "")
        return ;


    int  x = m_rect.x();

    int y = m_rect.y();

    int w = m_rect.width();

    int h = m_rect.height();

    conf.setValue("Base/type",m_dDefine[m_sType]);

    qDebug()<<"write : "<<m_sObjPath<<"type : "<<m_dDefine[m_sType]<<", "<<m_sType;


    conf.setValue("Base/x",x);

    conf.setValue("Base/y",y);

    conf.setValue("Base/w",w);

    conf.setValue("Base/h",h);

    conf.setValue("Base/changeTimer",5);

    conf.setValue("Action/cmd",m_dataCmd.sCmd);

    conf.setValue("Action/value1",m_dataCmd.sValue1);

    conf.setValue("Action/value2",m_dataCmd.sValue2);

    conf.sync();

    QString sSourcePath = m_sObjPath+"/source/";

    QString sSourcePathTmp = m_sObjPath+"/sourceTmp/";

    deleteDirectory(sSourcePathTmp);

    QDir().mkdir(sSourcePathTmp);


    if(m_sWaitRename.trimmed()!="")
    {
        deleteDirectory(m_sWaitRename);

        m_sWaitRename = "";
    }


    if(m_sType == E_PIC)
    {




        QStringList listName = m_dataPic.listPicName;

        conf.setValue("Pic/changeTimer",m_dataPic.iSec);


        for(int i=0;i<listName.length();i++)
        {
            //QPixmap *p = & m_dataPic.listPic[i];

            //    p->save(sSourcePathTmp+listName.at(i).split("/").last());

            //  QFile::copy( m_dataPic.listPicName.at(i)  ,sSourcePathTmp+listName.at(i).split("/").last());

            QString sOrigin= m_dataPic.listPicName.at(i);

            QString sFileName = "p"+QString::number(i);

            QString sType = listName.at(i).split(".").last();

            QString sPathName = sSourcePathTmp+sFileName+"."+sType;
            qDebug()<<"path name aa : "<< m_dataPic.listPicName.at(i) << "  , "<<sPathName;



            if(!QFile::exists(sOrigin))
            {
                sOrigin = m_sObjPath+"/source/"+m_dataPic.listPicName.at(i);
            }


            QFile::copy( sOrigin  ,sPathName);

            m_dataPic.listPicName[i] = sFileName+"."+sType;

        }


        qDebug()<<"AAAAAAAAAAA : "<< m_dataPic.listPicName;

        conf.setValue("Pic/list", m_dataPic.listPicName);



        deleteDirectory(sSourcePath);

        QDir().rename(sSourcePathTmp,sSourcePath);


    }



    else if(m_sType == E_VIDEO)
    {



        QStringList listName = m_dataVideo.listName;


        for(int i=0;i<listName.length();i++)
        {

            QString sTargetTmp =sSourcePathTmp+listName.at(i).split("/").last();
            QString sTarget =sSourcePath+listName.at(i).split("/").last();
            qDebug()<<"file : "<<listName.at(i);
            qDebug()<<"save : "<<sTarget;

            if(m_dataVideo.bHasChange)
            {
                QDir().mkdir(sSourcePathTmp);


                QFile::copy(listName.at(i),sTargetTmp);
            }
            listName[i] = sTarget;

        }

        conf.setValue("Video/mute",m_dataVideo.bIsMute);

        conf.setValue("Video/rtsp",m_dataVideo.sRtsp);

        conf.setValue("Video/useFile",m_dataVideo.bUseFile);

        conf.setValue("Video/list",listName);


        if(m_dataVideo.bHasChange)
        {

            deleteDirectory(sSourcePath);

            QDir().rename(sSourcePathTmp,sSourcePath);

        }

    }

    else if(m_sType == E_GRID)
    {
        if(m_dataGrid.bHasChange)
        {

            QDir().mkdir(sSourcePathTmp);


            for(int i=0;i<9;i++)
            {
                QString sPathG1 = sSourcePathTmp+QString::number(i+1);

                if(!QDir(sPathG1).exists())
                    QDir().mkdir(sPathG1);

                // QPixmap p(m_dataGrid.listG1.at(i));

                //  p.save(sPathG1+QString("/%1.png").arg(i+1),"PNG");

                QFile::copy(m_dataGrid.listG1.at(i),sPathG1+QString("/%1.png").arg(i+1));

                for(int j=0;j<9;j++)
                {
                    QString sPathG2=sPathG1+"/"+QString::number(j+1);
                    if(!QDir(sPathG2).exists())
                        QDir().mkdir(sPathG2);

                    //                    QPixmap p2(m_dataGrid.listG2[i].at(j));

                    //                    p2.save(sPathG2+QString("/%1.png").arg(j+1),"PNG");

                    QFile::copy(m_dataGrid.listG2[i].at(j),sPathG2+QString("/%1.png").arg(j+1));

                    //                    QPixmap p3(m_dataGrid.listG3[i].at(j));

                    //                    p3.save(sPathG2+QString("/%1_d.png").arg(j+1),"PNG");

                    QFile::copy(m_dataGrid.listG3[i].at(j),sPathG2+QString("/%1_d.png").arg(j+1));


                }
            }

            deleteDirectory(sSourcePath);

            QDir().rename(sSourcePathTmp,sSourcePath);



        }


        conf.setValue("Grid/count",m_dataGrid.iCount);

        m_dataGrid.bHasChange = false;


    }

    else if(m_sType == E_TXVALUE)
    {


        auto fnSavePic =[=](QString sKey)
        {


            QString sPath = m_data[sKey].toString();


            QString sTarget =sSourcePath+QString("%1.png").arg(sKey);

            QString sTargetTmp =sSourcePathTmp+QString("%1.png").arg(sKey);


            QFile::copy(sPath,sTargetTmp);

            qDebug()<<"key : "<<sKey<<" open : "<<sPath<<" ,target : "<<sTarget;


            m_data[sKey] = sTarget;


        };

        fnSavePic(TxtValue::imagePath);

        fnSavePic(TxtValue::imagePathMin);

        fnSavePic(TxtValue::imagePathMax);


        deleteDirectory(sSourcePath);

        QDir().rename(sSourcePathTmp,sSourcePath);



    }





    QStringList listKey = m_data.keys();

    conf.beginGroup("Items");


    if(m_data[Label::imagePath].toString()!="")
    {

        //QImage image(m_data["originImage"].toString());

        // image.save(m_sObjPath+"/bg.png");

        QFile::copy(m_data["originImage"].toString(),m_sObjPath+"/bg.png");


        m_data[Label::imagePath] = m_sObjPath.split("bin").last()+"/bg.png";
    }

    for(int i=0;i<listKey.length();i++)
    {

        QString sKey = listKey.at(i);


        QVariant target = m_data[sKey];

        conf.setValue(sKey,target);

    }

    conf.endGroup();



    //    qDebug()<<"write itemdata : "<<m_data;


    conf.sync();



}

bool ObjData::deleteDirectory(const QString &path)
{
    if (path.isEmpty())
        return false;

    QDir dir(path);
    if(!dir.exists())
        return true;

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList)
    {
        if (fi.isFile())
            fi.dir().remove(fi.fileName());
        else
            deleteDirectory(fi.absoluteFilePath());
    }
    return dir.rmpath(dir.absolutePath());

}



