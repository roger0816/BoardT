#include "DisplayContent.h"
#include "ui_DisplayContent.h"

DisplayContent::DisplayContent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayContent)
{
    ui->setupUi(this);

//    QString sBg = "C:/Users/chenchaowei/Documents/work/BoardT/bin/dataB/layerBK/model0/14_6/10-6.png";

    ui->wBg->setObjectName("DisplayContent_Bg_");

//    ui->wBg->setStyleSheet("QWidget#"+ui->wBg->objectName()+"{border-image:url("+sBg+");}");

   //ui->wBg->setStyleSheet("QWidget#"+ui->wBg->objectName()+"{border: 2px groove blue; border-style: outset; border-image:url(C:/Users/chenchaowei/Documents/work/BoardT/bin/dataB/layerBK/model0/14_2/10-2.png);}");


   //    ui->wBg->setStyleSheet("border-image:url('C:/Users/chenchaowei/Documents/work/BoardT/bin/dataB/layerBK/model0/14_2/10-2.png');");
}

DisplayContent::~DisplayContent()
{
    delete ui;
}

QString DisplayContent::setNewContent(QString sType)
{

    QString sName="";

    ItemContent *item = new ItemContent(this);

    item->connect(item,SIGNAL(sendUpdate()),this,SLOT(slotItemChange()));

    item->connect(item,SIGNAL(sendFocus()),this,SLOT(slotFocus()));

    if(sType ==E_TEXT)
    {
    item->m_iType = m_dDefine.value(E_TEXT);


    int iIdx = 0;

    QString sTmp = "TEXT_%1";

    while(!checkNewName(sTmp.arg(iIdx)))
        iIdx++;



    item->m_sName = sTmp.arg(iIdx);

    sName = item->m_sName;



    m_listItem.append(item);


    item->setRoll(true);

    setTxData(DataText());

    item->setGeometry(10,10,160,100);

    item->show();


    }

    return sName;
}

void DisplayContent::setBgImage(QString sPath)
{
    m_sBgPath = sPath;

    ui->wBg->setStyleSheet("QWidget#"+ui->wBg->objectName()+"{border-image:url("+sPath+");}");
}

bool DisplayContent::checkNewName(QString sName)
{
    bool bRe = true;

    foreach(ItemContent *item,m_listItem)
    {
        if(item->m_sName == sName)
            bRe = false;
    }

    return bRe;
}

void DisplayContent::setTypeMapping(QString sFile)
{

    QSettings defin(sFile,QSettings::IniFormat);

    m_dDefine.clear();

    QStringList listDefineKey= defin.allKeys();

    for(int i=0; i < listDefineKey.length();i++)
    {
        QString sKey = listDefineKey.at(i);

        int iValue = defin.value(sKey).toInt();

        m_dDefine.insert(sKey,iValue);
    }

}

QString DisplayContent::currentItemType()
{
    QString sRe="";

    sRe = m_dDefine.key(m_currentItem->m_iType);

    return sRe;
}

void DisplayContent::saveFile(QString sPath)
{
    if(!QDir(sPath).exists())
        QDir().mkdir(sPath);

    m_sPath = sPath;

//    QFile pro(sPath+"/"+sPath.split("/").last()+".BDT");

//    pro.open(QIODevice::WriteOnly);

//    //pro.write("");

//    pro.close();

    QSettings conf(sPath+"/"+sPath.split("/").last()+".BDT",QSettings::IniFormat);

    conf.setValue("Base/resumeTimer",15);

    conf.sync();

    if(m_sBgPath!="" && m_sBgPath !=sPath+"/bg.png")
    {
        QImage image(m_sBgPath);

        image.save(sPath+"/bg.png");

    }



    foreach(ItemContent *item ,m_listItem)
    {
        if(item->m_iType==m_dDefine.value(E_TEXT))
        {

            QString sItemDir = sPath+"/"+item->m_sName;

            QDir().mkdir(sItemDir);


            if(item->m_dataText.m_sImagePath!="")
            {
                QImage image(item->m_dataText.m_sImagePath);

                image.save(sItemDir+"/bg.png");
            }



            QSettings conf(sItemDir+"/conf.ini",   QSettings::IniFormat);

            conf.setValue("Base/type",item->m_iType);

            int  x =item->pos().x()/m_fDiffSize;

            int y = item->pos().y()/m_fDiffSize;

            int w = item->width()/m_fDiffSize;

            int h = item->height()/m_fDiffSize;

            conf.setValue("Base/x",x);

            conf.setValue("Base/y",y);

            conf.setValue("Base/w",w);

            conf.setValue("Base/h",h);

            conf.setValue("Base/changeTimer",5);

            //
            int iTxtSize =item->m_dataText.iPixSize/m_fDiffSize;
            conf.setValue("Title/txtSize",iTxtSize);

            QString sRgba("%1%2%3%4");


            QString sTxtColor = sRgba.arg(item->m_dataText.textColor.red(),2,16,QLatin1Char( '0' ))
                    .arg(item->m_dataText.textColor.green(),2,16,QLatin1Char( '0' ))
                    .arg(item->m_dataText.textColor.blue(),2,16,QLatin1Char( '0' ))
                    .arg(item->m_dataText.textColor.alpha(),2,16,QLatin1Char( '0' ));

            QString sBgColor = sRgba.arg(item->m_dataText.bgColor.red(),2,16,QLatin1Char( '0' ))
                    .arg(item->m_dataText.bgColor.green(),2,16,QLatin1Char( '0' ))
                    .arg(item->m_dataText.bgColor.blue(),2,16,QLatin1Char( '0' ))
                    .arg(item->m_dataText.bgColor.alpha(),2,16,QLatin1Char( '0' ));

            conf.setValue("Title/txtColor",sTxtColor);

            conf.setValue("Title/bgColor",sBgColor);

            int iTemp = item->m_dataText.bIsCent;

            conf.setValue("Title/alignCenter",iTemp);

            conf.sync();

            QFile file(sItemDir+"/text.txt");

            if(file.open(QIODevice::WriteOnly))
            {

                QString st = item->m_dataText.sText;

                file.write(st.toLatin1());

            }

            file.close();



            //            [Base]
            //            x=2
            //            y=1580
            //            w=1080
            //            h=150
            //            type=1
            //            changeTimer=5

            //            [Title]

            //            txtSize=42

            //            ;色碼RGBA
            //            txtColor=FF000088
            //            bgColor=0A0A0A66

            //            alignCenter=1
            //            marquee=0



        }



    }


}

void DisplayContent::loadFile(QString sPath)
{
    m_sPath = sPath;

    QFileInfo file(sPath);

    QString sDir = file.path();


    clearUi();


    setBgImage(sPath+"/bg.png");


    QFileInfoList listDir = QDir(sPath).entryInfoList(QDir::AllDirs);




    for(int i=0;i<listDir.length();i++)
    {
        QFileInfo dir = listDir.at(i);

        if(dir.fileName()!="." && dir.fileName()!="..")
        {

            qDebug()<<dir.filePath();

            QFileInfo conf(dir.filePath()+"/conf.ini");

            if(conf.exists())
            {


                QSettings conf(dir.filePath()+"/conf.ini",QSettings::IniFormat);


                QString sType = m_dDefine.key(conf.value("Base/type").toInt());

                if(sType =="")
                    continue;

                if(sType==E_TEXT)
                {

                    setNewContent(E_TEXT);

                    ItemContent *item = m_listItem.last();

                    item->m_sName = dir.fileName();

                    int x = conf.value("Base/x").toInt()*m_fDiffSize;

                    int y = conf.value("Base/y").toInt()*m_fDiffSize;

                    int w = conf.value("Base/w").toInt()*m_fDiffSize;

                    int h = conf.value("Base/h").toInt()*m_fDiffSize;

                    item->setGeometry(x,y,w,h);

                    DataText data;

                    if(QFileInfo(dir.filePath()+"/bg.png").exists())
                    {
                        data.m_sImagePath = dir.filePath()+"/bg.png";
                    }

                    data.bIsCent = conf.value("Title/alignCenter").toBool();

                    data.iPixSize = conf.value("Title/txtSize").toInt()*m_fDiffSize;

                    bool bOk;

                    int iBgR = conf.value("Title/bgColor").toString().mid(0,2).toInt(&bOk,16);

                    int iBgG = conf.value("Title/bgColor").toString().mid(2,2).toInt(&bOk,16);

                    int iBgB = conf.value("Title/bgColor").toString().mid(4,2).toInt(&bOk,16);

                    int iBgA = conf.value("Title/bgColor").toString().mid(6,2).toInt(&bOk,16);

                    data.bgColor = QColor(iBgR,iBgG,iBgB,iBgA);

                    int iTxR = conf.value("Title/txtColor").toString().mid(0,2).toInt(&bOk,16);

                    int iTxG = conf.value("Title/txtColor").toString().mid(2,2).toInt(&bOk,16);

                    int iTxB = conf.value("Title/txtColor").toString().mid(4,2).toInt(&bOk,16);

                    int iTxA = conf.value("Title/txtColor").toString().mid(6,2).toInt(&bOk,16);


                    data.textColor = QColor(iTxR,iTxG,iTxB,iTxA);


                    QFileInfoList listTxt = QDir(dir.filePath()).entryInfoList(QStringList()<<"*.txt");

                    qDebug()<<listTxt.first().filePath();

                    QString sTxt="";

                    QFile file(listTxt.first().filePath());

                    if(file.open(QIODevice::ReadOnly))
                    {
                        sTxt = file.readAll();

                        item->m_dataText.sText = sTxt;

                        file.close();

                    }

                    data.sText = sTxt;

                    setTxData(data,m_listItem.indexOf(item));


                }

            }

//            m_listDir.append(dir);

//            while(m_listContent.length()<=i)
//            {
//                m_listContent.append(new LayerContent(ui->wBg));

//                m_listContent.last()->hide();
//            }

//            m_listContent[i]->setPath(dir.filePath(),m_dDefine);

            //  m_listContent[i]->show();
        }
    }

}

void DisplayContent::clearUi()
{
    qDeleteAll(m_listItem);

    m_listItem.clear();


    m_sBgPath="";


    setBgImage("bg.png");

}

void DisplayContent::setTxData(DataText txData,int iIdx)
{

    ItemContent *item = m_currentItem;

    if(iIdx<m_listItem.length() && iIdx>= 0 )
        item = m_listItem[iIdx];

    if(item==nullptr)
        return ;


    if(m_currentItem->m_iType != m_dDefine.value(E_TEXT))
        return ;

    DataText data = txData;

    item->setBgColor(data.bgColor);

    item->setBg(data.m_sImagePath);

    item->m_dataText = data;

    QLabel *lb =  item->lb;

    lb->setText(data.sText);

    QFont f;

    f.setPixelSize(data.iPixSize*m_fDiffSize);

    lb->setFont(f);

    QString sStyle = "color:rgba(%1,%2,%3,%4);"
                     "background-color:rgba(0,0,0,0);";

    lb->setStyleSheet(sStyle.arg(data.textColor.red())
                      .arg(data.textColor.green())
                      .arg(data.textColor.blue())
                      .arg(data.textColor.alpha())
//                      .arg(data.bgColor.red())
//                      .arg(data.bgColor.green())
//                      .arg(data.bgColor.blue())
                    //  .arg(data.bgColor.alpha())

                      );

    if(data.bIsCent)
        lb->setAlignment(Qt::AlignCenter);
    else
        lb->setAlignment(Qt::AlignLeading);






}

void DisplayContent::rename(QString sName)
{
    if(m_currentItem == nullptr)
        return ;

    QString sOldName = m_currentItem->m_sName;

    if(m_currentItem->m_sName == sName)
        return ;
    m_currentItem->m_sName = sName;

    QDir dir(m_sPath+"/"+sOldName);

    if(dir.exists())
    {
        dir.rename(m_sPath+"/"+sOldName,m_sPath+"/"+sName);

    }



}

void DisplayContent::resizeEvent(QResizeEvent *)
{

    float f = float(1080)/1920;


    setMinimumWidth(height()*f);

    setMaximumWidth(height()*f);

    m_fDiffSize = float(height())/1920;



}

void DisplayContent::slotItemChange()
{

    if(sender()==m_currentItem)
        emit sendItemUpdate();
}



void DisplayContent::slotFocus()
{

        ItemContent *item = dynamic_cast<ItemContent*>(sender());

        m_currentItem = item;

       // editType(m_currentItem->m_iType);


        foreach(ItemContent *target,m_listItem)
        {
            if(target!=item)
            {
                target->setRoll(false);
            }
        }

    emit sendItemUpdate();
}

