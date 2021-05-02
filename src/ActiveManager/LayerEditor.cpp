#include "LayerEditor.h"
#include "ui_LayerEditor.h"

LayerEditor::LayerEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerEditor)
{
    ui->setupUi(this);

    ui->stackType->setCurrentWidget(ui->pageText);

}

LayerEditor::~LayerEditor()
{
    delete ui;
}

void LayerEditor::setTarget(QString sObjPath)
{
    qDebug()<<"change focus : "<<sObjPath;
    m_sPath = sObjPath;

    QStringList listTmp = m_sPath.split("/");



    if(listTmp.length()<2)
        return;

    bool bOk = false;

    m_sLayerName = listTmp.at(listTmp.length()-2);

    m_sObjName = listTmp.at(listTmp.length()-1);

    ObjData *data = CDATA.getObj(m_sLayerName,m_sObjName,bOk);

    if(!bOk)
        return;

    m_obj = data;


    refresh();

}

void LayerEditor::refresh()
{



    if(m_obj == nullptr)
        return;


    qDebug()<<"refresh ";


    m_bLockCallUpdate = true;

    ui->txtName->setText(m_obj->m_sName);

    ui->sbX->setValue(m_obj->m_rect.x());

    ui->sbY->setValue(m_obj->m_rect.y());

    ui->sbW->setValue(m_obj->m_rect.width());

    ui->sbH->setValue(m_obj->m_rect.height());


    if(m_obj->m_sType == E_TEXT)
    {

        ui->stackType->setCurrentWidget(ui->pageText);

        ui->txtText->setText(m_obj->m_dataText.sText);

        ui->chCent->setChecked(m_obj->m_dataText.bIsCent);


        QColor colorBg = m_obj->m_dataText.bgColor;

        QColor colorTxt = m_obj->m_dataText.textColor;

        QString sStyle = "background-color:rgba(%1,%2,%3,%4);";

        ui->btnBgColor->setStyleSheet(sStyle.arg(colorBg.red()).arg(colorBg.green())
                                      .arg(colorBg.blue()).arg(colorBg.alpha()));

        ui->btnTxtColor->setStyleSheet(sStyle.arg(colorTxt.red()).arg(colorTxt.green())
                                       .arg(colorTxt.blue()).arg(colorTxt.alpha()));


    }
    else if(m_obj->m_sType == E_PIC)
    {

        ui->stackType->setCurrentWidget(ui->pagePic);

        ui->sbPicSec->setValue(m_obj->m_dataPic.iSec);

    }

    else if(m_obj->m_sType == E_VIDEO)
    {

        ui->stackType->setCurrentWidget(ui->pageVideo);



    }

    m_bLockCallUpdate =false;
}

void LayerEditor::on_btnTxtColor_clicked()
{

    QStringList listTmp = m_sPath.split("/");

    if(listTmp.length()<2)
        return;

    bool bOk = false;

    ObjData *data = CDATA.getObj(listTmp.at(listTmp.length()-2),listTmp.at(listTmp.length()-1),bOk);

    if(!bOk)
        return;

    QColor txColor = data->m_dataText.textColor;




    QColorDialog dialog;

    dialog.setOption(QColorDialog::ShowAlphaChannel);

    if(m_bFristTxColor)
    {
        txColor = Qt::white;

        m_bFristTxColor = false;

    }
    QColor color = dialog.getColor(txColor); //,nullptr,"",QColorDialog::ShowAlphaChannel);

    QPushButton *btn = dynamic_cast<QPushButton*>(sender());

    QString sStyle ="background-color:rgba(%1,%2,%3,%4);";

    btn->setStyleSheet(sStyle.arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()));

    data->m_dataText.textColor = color;

    emit callUpdate();
}

void LayerEditor::on_btnBgColor_clicked()
{
    QStringList listTmp = m_sPath.split("/");

    if(listTmp.length()<2)
        return;

    bool bOk = false;

    ObjData *data = CDATA.getObj(listTmp.at(listTmp.length()-2),listTmp.at(listTmp.length()-1),bOk);

    if(!bOk)
        return;

    QColor bgColor = data->m_dataText.bgColor;


    QColorDialog dialog;

    dialog.setOption(QColorDialog::ShowAlphaChannel);

    if(m_bFristBgColor)
    {
        bgColor = Qt::white;

        m_bFristBgColor = false;

    }
    QColor color = dialog.getColor(bgColor); //,nullptr,"",QColorDialog::ShowAlphaChannel);

    QPushButton *btn = dynamic_cast<QPushButton*>(sender());

    QString sStyle ="background-color:rgba(%1,%2,%3,%4);";

    btn->setStyleSheet(sStyle.arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()));

    data->m_dataText.bgColor = color;

    emit callUpdate();
}

void LayerEditor::on_sbX_valueChanged(int)
{
    readyCallUpdate();
}


void LayerEditor::on_sbY_valueChanged(int )
{
    readyCallUpdate();
}

void LayerEditor::on_sbW_valueChanged(int )
{
    readyCallUpdate();
}

void LayerEditor::on_sbH_valueChanged(int )
{
    readyCallUpdate();
}

void LayerEditor::readyCallUpdate()
{
    if(m_obj ==nullptr || m_bLockCallUpdate )
        return ;

    m_obj->m_rect.setX(ui->sbX->value());

    m_obj->m_rect.setY(ui->sbY->value());

    m_obj->m_rect.setWidth(ui->sbW->value());

    m_obj->m_rect.setHeight(ui->sbH->value());

    m_obj->m_dataText.sText = ui->txtText->text();

    m_obj->m_dataText.bIsCent = ui->chCent->isChecked();

    emit callUpdate();
}

bool LayerEditor::deleteDirectory(const QString &path)
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


void LayerEditor::on_txtText_textChanged(const QString &)
{
    readyCallUpdate();
}

void LayerEditor::on_spSize_valueChanged(int)
{
    readyCallUpdate();
}

void LayerEditor::on_chCent_clicked()
{
    readyCallUpdate();
}

void LayerEditor::on_btnToTop_clicked()
{
    emit callRaise(m_sPath);
}

void LayerEditor::on_btnRename_clicked()
{
    if(m_obj == nullptr)
    {
        return ;
    }


    if(m_sPath.split("/").last().trimmed() == ui->txtName->text())
        return ;

    QString sOldPath = m_sPath;

    QStringList listTmp = m_sPath.split("/");

    listTmp.pop_back();

    listTmp.push_back(ui->txtName->text());

    QString sNewPath = listTmp.join("/");

    m_obj->m_sName = listTmp.last();

    qDebug()<<"m_obj name : "<<m_obj->m_sName;

    m_obj->m_sObjPath = sNewPath;

    QDir().rename(sOldPath,sNewPath);

    m_sPath = sNewPath;


    emit callRename(sOldPath,sNewPath);
    // callUpdate();



}

void LayerEditor::on_btnBgImage_clicked()
{

    if(m_obj == nullptr)
        return;

    QString sPath = QFileDialog::getOpenFileName(this,"選擇元件背景圖",QApplication::applicationDirPath(),"*.png");

    if(m_obj->m_dataText.m_sImagePath!= sPath)
    {
        m_obj->m_dataText.m_sImagePath=sPath;

        emit callUpdate();
    }
}

void LayerEditor::on_btnCmd_clicked()
{

}

void LayerEditor::on_txtBgImage_textChanged(const QString &arg1)
{

}

void LayerEditor::on_btnClearBg_clicked()
{
    if(m_obj==nullptr)
        return;

    if(m_obj->m_dataText.m_sImagePath!="")
    {
        m_obj->m_dataText.m_sImagePath="";

        emit callUpdate();
    }
}

void LayerEditor::on_btnSelectFont_clicked()
{

    if(m_obj == nullptr)
        return;

    QFont iniFont=ui->btnSelectFont->font();
    bool   ok=false;
    QFont font=QFontDialog::getFont(&ok,iniFont);
    if (ok)
        ui->btnSelectFont->setFont(font);

    m_obj->m_dataText.font = font;

    callUpdate();
    //font.toString()
}

void LayerEditor::on_btnDelete_clicked()
{
    DialogMsg msg;

    msg.setDialogInfo("確定要刪除此元件嗎？",QStringList()<<"否"<<"是");

    int iRe = msg.exec();

    if(iRe==1)
    {

        emit callDelete(m_sPath);


        deleteDirectory(m_sPath);
    }


}

void LayerEditor::on_btnSetPic_clicked()
{
    QStringList listSelect =QFileDialog::getOpenFileNames(this,
                             QStringLiteral("選取圖檔"),
                            QApplication::applicationDirPath(),
                             QStringLiteral("*.png"));


    bool bOk = false;

    ObjData *data = CDATA.getObj(m_sLayerName,m_sObjName,bOk);

    if(!bOk)
        return;

    QList<QPixmap> *list = &data->m_dataPic.listPic;

    QStringList *listName = &data->m_dataPic.listPicName;


    list->clear();

    listName->clear();


    for(int i=0;i<listSelect.length();i++)
    {

        QPixmap p(listSelect.at(i));

        list->append(p);

        listName->append(listSelect.at(i).split("/").last());
    }



}

void LayerEditor::on_sbPicSec_valueChanged(int )
{
    bool bOk = false;

    ObjData *data = CDATA.getObj(m_sLayerName,m_sObjName,bOk);

    if(!bOk)
        return;

    data->m_dataPic.iSec = ui->sbPicSec->value();

}

void LayerEditor::on_btnVideoSet_clicked()
{
    bool bOk = false;

    ObjData *data = CDATA.getObj(m_sLayerName,m_sObjName,bOk);

    if(!bOk)
        return;

    QStringList listSelect =QFileDialog::getOpenFileNames(this,
                             QStringLiteral("選取影片"),
                            QApplication::applicationDirPath()+"/video",
                             QStringLiteral("*.mp4"));



    QStringList *listName = &data->m_dataVideo.listName;

    listName->clear();

}
