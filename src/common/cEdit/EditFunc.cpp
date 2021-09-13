#include "EditFunc.h"

EditFunc::EditFunc(QObject *parent) : QObject(parent)
{

}

bool EditFunc::setColor(ObjData *obj, QString sDataKey, QPushButton *btn)
{
    Q_UNUSED(btn);

    if(obj == nullptr)
        return false;

    QString sTmp = obj->m_data.value(sDataKey).toString().replace("#","");

    while(sTmp.length()<8)
        sTmp.append("f");

    QColor txColor;

    bool b;

    txColor.setRed(sTmp.midRef(0,2).toInt(&b,16));
    txColor.setGreen(sTmp.midRef(2,2).toInt(&b,16));
    txColor.setBlue(sTmp.midRef(4,2).toInt(&b,16));
    txColor.setAlpha(255);
    QVariant var;

    bool bRe = setColor(txColor,var);

    if(bRe)
    {
        obj->m_data[sDataKey] = var;
    }

    return bRe;

    //    QColorDialog dialog;

    //    dialog.setOption(QColorDialog::ShowAlphaChannel);

    //    //    if(m_bFristTxColor)
    //    //    {
    //    //        txColor = Qt::white;

    //    //        m_bFristTxColor = false;

    //    //    }
    //    QColor color = dialog.getColor(txColor,nullptr,"",QColorDialog::ShowAlphaChannel);



    //    obj->m_data[sDataKey] = color.name(QColor::HexArgb);

}

bool EditFunc::setColor(QColor current, QVariant &var)
{

    QColorDialog dialog;

    dialog.setOption(QColorDialog::ShowAlphaChannel);

    //    if(m_bFristTxColor)
    //    {
    //        txColor = Qt::white;

    //        m_bFristTxColor = false;

    //    }

    dialog.setCurrentColor(current);

    QColor color = dialog.getColor(current,nullptr,"",QColorDialog::ShowAlphaChannel);

    qDebug()<<"SS0 : "<<color;

    var = QVariant(color.name()+QString("%1").arg(color.alpha(), 2, 16, QLatin1Char('0')));

    qDebug()<<"SS1 : "<<var;

    //     var = QVariant("#"+QString::number(color.red(),16)
    //                +QString::number(color.green(),16)
    //     +QString::number(color.blue(),16)
    //     +QString::number(color.alpha(),16));


    return color.isValid();

}



void EditFunc::setFont(ObjData *obj, QString sDataKey, QPushButton *btn)
{

    if(obj == nullptr || btn ==nullptr)
        return;

    QFont iniFont ;

    QString sFont = obj->m_data.value(sDataKey,"Arial,24,-1,5,50,0,0,0,0,0,Regular").toString();

    iniFont.fromString(sFont);

    setFont(iniFont);

    obj->m_data[sDataKey] = iniFont;

    //    bool   ok=false;
    //    QFont font=QFontDialog::getFont(&ok,iniFont);
    //    if (ok)
    //    {
    //      //  btn->setFont(font);
    //        QString sTmp="字型\n%1,%2,%3";
    //        font.toString();

    //        QStringList listTmp  = font.toString().split(",");

    ////        if(listTmp.length()>2)
    ////            btn->setText(sTmp.arg(listTmp.first()).arg(listTmp.at(1)).arg(listTmp.last()));

    //        obj->m_data[sDataKey] = font;
    //    }

    //font.toString()

}

bool EditFunc::setFont(QFont &current)
{
    bool   ok=false;
    QFont font=QFontDialog::getFont(&ok,current);
    if (ok)
    {
        //  btn->setFont(font);
        QString sTmp="字型\n%1,%2,%3";
        font.toString();

        QStringList listTmp  = font.toString().split(",");

        //        if(listTmp.length()>2)
        //            btn->setText(sTmp.arg(listTmp.first()).arg(listTmp.at(1)).arg(listTmp.last()));

        current = font;
    }

    return ok;
}

void EditFunc::setCent(ObjData *obj, QString sDataKey, QCheckBox *btn)
{
    if(obj ==nullptr || btn ==nullptr)
        return ;

    int iClicked = btn->isChecked();

    obj->m_data[sDataKey] = iClicked;

}

void EditFunc::setBgImage(ObjData *obj, QString sTitle,QString sDataKey)
{
    QString sPath = QFileDialog::getOpenFileName(nullptr,sTitle,QApplication::applicationDirPath(),"*.png");

    if(obj->m_data.value(sDataKey)!= sPath)
    {
        //obj->m_data[sDataKey] = sPath;

        obj->m_data["originImage"] = sPath;

        obj->m_data[sDataKey] = obj->m_sObjPath.split("bin").last()+"/bg.png";
    }


}

void EditFunc::clearBgImage(ObjData *obj, QString sDataKey)
{
    if(obj->m_data.value(sDataKey).toString()!="")
    {
        obj->m_data[sDataKey] = "";

    }
}


