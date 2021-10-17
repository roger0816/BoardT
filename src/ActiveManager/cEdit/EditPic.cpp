#include "EditPic.h"
#include "ui_EditPic.h"

EditPic::EditPic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditPic)
{
    ui->setupUi(this);


    ui->tb->horizontalHeader()->setVisible(true);

}

EditPic::~EditPic()
{
    delete ui;
}

void EditPic::setTarget(ObjData *obj)
{

    m_obj = obj;

    readData();

    refreshTable();
}

void EditPic::showEvent(QShowEvent *)
{
    ui->tb->setColumnWidth(0,ui->tb->width()-80-3);

    ui->tb->setColumnWidth(1,80);
}

void EditPic::readData()
{
    if(m_obj==nullptr)
        return ;

    ui->sbPicSec->setValue(m_obj->m_dataPic.iSec);

}

void EditPic::refreshTable()
{
    ui->tb->setRowCount(0);

    for(int i=0;i<m_obj->m_dataPic.listPicName.length();i++)
    {
        ui->tb->setRowCount(i+1);

        QTableWidgetItem *item= new QTableWidgetItem(m_obj->m_dataPic.listPicName.at(i));

        ui->tb->setItem(i,0,item);

        QLabel *lb = new QLabel(ui->tb);

        lb->setAlignment(Qt::AlignCenter);

        lb->setPixmap(QPixmap(m_obj->m_dataPic.listPic.at(i)).scaledToHeight(60));

        ui->tb->setCellWidget(i,1,lb);

        ui->tb->setColumnWidth(0,ui->tb->width()-80-3);

        ui->tb->setColumnWidth(1,80);
    }
}

void EditPic::on_btnSetPic_clicked()
{



    if(m_obj==nullptr)
        return;

    QList<QPixmap> *list = &m_obj->m_dataPic.listPic;


    QStringList listSelect = m_obj->m_dataPic.listPicName;


    DialogSelectFile select;

    select.setFileList(listSelect,m_obj->m_sObjPath);

    select.exec();

    listSelect = select.fileList();


    list->clear();

    m_obj->m_dataPic.listPicName.clear();


    for(int i=0;i<listSelect.length();i++)
    {

        QPixmap p(listSelect.at(i));

        list->append(p);

        m_obj->m_dataPic.listPicName.append(listSelect.at(i));

        //   data->m_dataPic.listOriginPath.append(listSelect.at(i));
    }

    refreshTable();

}

void EditPic::on_sbPicSec_valueChanged(int)
{
    bool bOk = false;

    if(!bOk)
        return;

    m_obj->m_dataPic.iSec = ui->sbPicSec->value();

}
