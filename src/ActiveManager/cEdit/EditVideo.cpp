#include "EditVideo.h"
#include "ui_EditVideo.h"

EditVideo::EditVideo(QWidget *parent) :
    EditBase(parent),
    ui(new Ui::EditVideo)
{
    ui->setupUi(this);

    m_btnsRb.addButton(ui->rbVideo);

    m_btnsRb.addButton(ui->rbRtsp);
}

EditVideo::~EditVideo()
{
    delete ui;
}

void EditVideo::setTarget(ObjData *data)
{
    m_obj = data;

    ui->cbMute->setChecked(m_obj->m_dataVideo.bIsMute);

    refreshTable();
}

void EditVideo::refreshTable()
{
    ui->tb->setRowCount(0);


    if(m_obj==nullptr)
        return;


    for(int i=0;i<m_obj->m_dataVideo.listName.length();i++)
    {
        ui->tb->setRowCount(i+1);

        QTableWidgetItem *item= new QTableWidgetItem(m_obj->m_dataVideo.listName.at(i).split("/").last());

        ui->tb->setItem(i,0,item);

    }
}

void EditVideo::clearTable()
{
    ui->tb->setRowCount(0);
}

void EditVideo::on_btnSetting_clicked()
{

    if(m_obj==nullptr)
        return;

    QStringList listFile = m_obj->m_dataVideo.listName;

    DialogSelectFile dialog;

    dialog.setType(false,"*.mp4");

    dialog.setFileList(listFile);

    int iRe = dialog.exec();

    if(iRe!=1)
        return ;

    listFile = dialog.fileList();

    m_obj->m_dataVideo.listName = listFile;

    refreshTable();

    //    ObjData *data = CDATA.getObj(m_sLayerName,m_sObjName,bOk);


    //    QStringList listSelect =QFileDialog::getOpenFileNames(this,
    //                                                          QStringLiteral("選取影片"),
    //                                                          QApplication::applicationDirPath()+"/video",
    //                                                          QStringLiteral("*.mp4"));


    //    qDebug()<<"listselect video : "<<listSelect;
    //    QStringList *listName = &data->m_dataVideo.listName;

    //    listName->clear();

    //    listName->append(listSelect);



}

void EditVideo::on_cbMute_clicked(bool checked)
{
    if(m_obj==nullptr)
        return;

    m_obj->m_dataVideo.bIsMute = checked;
}
