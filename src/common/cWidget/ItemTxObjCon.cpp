#include "ItemTxObjCon.h"

ItemTxObjCon::ItemTxObjCon(QWidget *parent) : ItemLabel(parent)
{
    m_file.setFileName(QApplication::applicationDirPath()+"/input.txt");

    // startTimer(1000);

    connect(&m_timer,&QTimer::timeout,this,&ItemTxObjCon::slotTimer);

    m_timer.start(1000);

    m_listGpioPin<<0<<0<<0;

    m_listGpioValue<<0<<0<<0;

    m_lb->setText("Txt元件");




}

void ItemTxObjCon::init()
{
    updateItem();
}


void ItemTxObjCon::updateItem()
{
    // ItemLabel::updateItem();

    if(m_obj!=nullptr)
        m_data = m_obj->m_data;


    m_iReadSpeed = m_obj->m_data.value(TxtValue::readSpeed,2).toInt();

    m_iGpioSpeed = m_iReadSpeed;

    m_iPlaySpeed = m_obj->m_data.value(TxtValue::playSpeed,5).toInt();

    m_iSelect = m_obj->m_data.value(TxtValue::index,0).toInt();

    m_iLimitMin = m_obj->m_data.value(TxtValue::min,0).toDouble();

    m_iLimitMax = m_obj->m_data.value(TxtValue::max,99).toDouble();

    QStringList listText = m_obj->m_data.value(TxtValue::msg,"").toStringList();

    while(listText.length()<3)
    {
        listText.append("");
    }

    m_sMsgMin = listText.first();

    m_sMsgMax = listText.last();

    m_sMsg = listText.at(1);

    // m_lb->setText(m_data.value(TxtValue::msg,"Txt文字").toString());

    //    QColor bgColor = m_data.value(TxtValue::bgColor,"#ffffffff").toString();
    //    //bgColor.name(QColor::HexArgb)


    //    QColor txtColor = m_data.value(TxtValue::txtColor,"#ff000000").toString();


    //    if(m_data.value(TxtValue::alignCenter).toInt())
    //        m_lb->setAlignment(Qt::AlignCenter);
    //    else
    //        m_lb->setAlignment(Qt::AlignLeading);

    m_changeGpio = false;

    if(m_listGpioPin[0] != m_obj->m_data[TxtValue::gpioPinMin].toInt())
    {
        m_changeGpio = true;

        m_listGpioPin[0] = m_obj->m_data[TxtValue::gpioPinMin].toInt();

        setGpio(m_listGpioPin[0]);

    }

    if(m_listGpioPin[1] != m_obj->m_data[TxtValue::gpioPin].toInt())
    {
        m_changeGpio = true;

        m_listGpioPin[1] = m_obj->m_data[TxtValue::gpioPin].toInt();

        setGpio(m_listGpioPin[1]);
    }

    if(m_listGpioPin[2] != m_obj->m_data[TxtValue::gpioPinMax].toInt())
    {
        m_changeGpio = true;

        m_listGpioPin[2] = m_obj->m_data[TxtValue::gpioPinMax].toInt();

        setGpio(m_listGpioPin[2]);
    }


    m_iEditStatus = m_obj->m_dEditData["EditStatus"].toInt();


    doRead();

     qDebug()<<"update item";
}


void ItemTxObjCon::doRead()
{
    qDebug()<<"doRead";

    //  QFile f(QApplication::applicationDirPath()+"/input.txt");

    if(!QFile().exists(QApplication::applicationDirPath()+"/input.txt"))
    {
        return ;
    }


    QFile *file = new QFile(QApplication::applicationDirPath()+"/input.txt");


    if(file->open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QString st = file->readAll();


        QStringList list  = st.split(",");


        if( m_iSelect >=0  && list.length()>0 &&  m_iSelect < list.length() )
        {

            m_sCurrentValue = list.at(m_iSelect);

        }

        file->close();
    }

    if(m_sCurrentValue=="")
        m_sCurrentValue="0";



    delete file;


}

void ItemTxObjCon::doChangeShow()
{


    if(m_sCurrentValue=="" || m_sCurrentValue.toInt() <0 )
        return ;
    m_sCurrentMsg="";


    int iStatus = m_iEditStatus;

    if(!CDATA.m_bIsEdit)
    {
        if(m_sCurrentValue.toDouble() < m_iLimitMin)
        {
            iStatus = _MIN;

        }
        else if(m_sCurrentValue.toDouble() > m_iLimitMax )
        {
            iStatus = _MAX;
        }
        else
        {
            iStatus = _NORMAL;

        }
    }



    if(iStatus == _MIN)
    {

        m_sCurrentMsg = m_sMsgMin;

        setStatusStyle(_MIN);
    }

    else if(iStatus == _MAX)
    {

        m_sCurrentMsg = m_sMsgMax;

        setStatusStyle(_MAX);
    }
    else
    {
        m_sCurrentMsg = m_sMsg;

        setStatusStyle(_NORMAL);
    }

    QString sDisplay = m_sCurrentMsg;

    if(!m_bIsShowValue)
    {
        sDisplay = m_sCurrentValue;
    }

//    if((!m_bIsShowValue || m_sCurrentMsg=="" ) && !CDATA.m_bIsEdit)
//    {

//        sDisplay = m_sCurrentValue;
//    }

    m_bIsShowValue = !m_bIsShowValue;

    if(sDisplay.trimmed()=="0")
        sDisplay="";

    m_lb->setText(sDisplay);
}

void ItemTxObjCon::setStatusStyle(int i)
{

    m_status = i;


    QString bgColor = m_data.value(TxtValue::bgColor,"#ffffffff").toString();

    QString txtColor = m_data.value(TxtValue::txtColor,"#99999999").toString();

    QString sImagePath = m_data.value(TxtValue::imagePath).toString();

    QString sText=m_data.value(TxtValue::msg,"文字").toString();

    Qt::Alignment ali = Qt::AlignLeading;

    if(m_data.value(TxtValue::alignCenter).toInt())
        ali=Qt::AlignCenter;
    else
        ali=Qt::AlignLeading;


    QFont f ;
    f.fromString("Arial,24,-1,5,50,0,0,0,0,0,Regular");

    QString sFont = m_data.value(Label::font,"Arial,24,-1,5,50,0,0,0,0,0,Regular").toString();

    f.fromString(sFont);


    if(i == _MIN)
    {
        bgColor = m_data.value(TxtValue::bgColorMin,"#ffffffff").toString();

        txtColor = m_data.value(TxtValue::txtColorMin,"#99999999").toString();

        sImagePath = m_data.value(TxtValue::imagePathMin).toString();

        sText=m_data.value(TxtValue::min,"文字").toString();

        sFont = m_data.value(TxtValue::fontMin,"Arial,24,-1,5,50,0,0,0,0,0,Regular").toString();



        if(m_data.value(TxtValue::alignCenterMin).toInt())
            ali=Qt::AlignCenter;
        else
            ali=Qt::AlignLeading;
    }

    else if(i == _MAX)
    {
        bgColor = m_data.value(TxtValue::bgColorMax,"#ffffffff").toString();

        txtColor = m_data.value(TxtValue::txtColorMax,"#99999999").toString();

        sImagePath = m_data.value(TxtValue::imagePathMax).toString();

        sText=m_data.value(TxtValue::max,"文字").toString();

        if(m_data.value(TxtValue::alignCenterMax).toInt())
            ali=Qt::AlignCenter;
        else
            ali=Qt::AlignLeading;

        sFont = m_data.value(TxtValue::fontMax,"Arial,24,-1,5,50,0,0,0,0,0,Regular").toString();

    }

    f.fromString(sFont);


    QString sTxt = getStyleSheetRgba(txtColor);

    QString sBg = getStyleSheetRgba(bgColor);


//    if(sImagePath.trimmed()!="")
//    {


//        m_lb->setStyleSheet("QLabel#"+m_lb->objectName()+"{color:"+sTxt
//                                 +";background-color:rgba(0, 0, 0,0);border-image:url("+sImagePath+");}");

//    }
//    else
    {
        m_lb->setStyleSheet("QLabel#"+m_lb->objectName()+"{color:"+sTxt
                                 +";background-color:"+sBg+"}");

    }



#ifndef Q_OS_WINDOWS
    f.setPointSize(f.pointSize()*2.2);
#endif

    m_lb->setFont(f);


    m_lb->setText(sText);

    //  qDebug()<<"update alignCenter : "<<m_data.value(Label::alignCenter).toInt();
    //    if(m_data.value(Label::alignCenter).toInt())
    //        m_lb->setAlignment(Qt::AlignCenter);
    //    else
    m_lb->setAlignment(ali);







}

void ItemTxObjCon::setGpio(int iPin)
{
    if(CDATA.m_bIsEdit)
        return ;

    if(!QDir("/sys/class/gpio/").exists())
        return;

    QString sTmp ="echo "+QString::number(iPin)+" > /sys/class/gpio/export ";

    system(sTmp.toStdString().c_str());


    QString sTmp2 ="echo out > /sys/class/gpio/gpio"+QString::number(iPin)+"/direction";

    system(sTmp2.toStdString().c_str());
}

void ItemTxObjCon::sendGpio(int iPin, int iValue)
{
    if(CDATA.m_bIsEdit)
        return ;

    if(!QDir("/sys/class/gpio/").exists())
        return;

    QString sTmp="echo %2 > /sys/class/gpio/gpio%1/value";

    system(sTmp.arg(iValue).arg(iPin).toStdString().c_str());

}

void ItemTxObjCon::iniGpio()
{
    if(CDATA.m_bIsEdit)
        return ;
    foreach(int iPin,m_listGpioPin)
    {
        sendGpio(iPin,0);
    }

}

void ItemTxObjCon::slotTimer()
{


    m_iSec++;

    if(m_iSec>=10000)
        m_iSec=1;

    if(m_iReadSpeed<1)
        m_iReadSpeed = 1;

    if(m_iPlaySpeed <1)
        m_iPlaySpeed = 1;


    if(m_iSec%m_iReadSpeed==0)
    {
        if(!CDATA.m_bIsEdit)
        doRead();

    }



    if(m_iSec%m_iPlaySpeed==0)
    {

        doChangeShow();

    }

    if(m_iSec % m_iGpioSpeed == 0 &&  CDATA.m_bIsEdit)
    {
        int iPin = m_listGpioPin[m_status];

        int iValue =1;// = m_listGpioValue[m_status];

        // if(iPin != m_iPrePin)
        {
            iniGpio();

            sendGpio(iPin,iValue);
        }

        m_iPrePin = iPin;
    }



}
