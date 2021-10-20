#include "DialogEditGrid.h"
#include "ui_DialogEditGrid.h"

DialogEditGrid::DialogEditGrid(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditGrid)
{
    ui->setupUi(this);

    connect(ui->wG1,&LayerEditGrid::clicked,this,&DialogEditGrid::slotItemClicked);

    connect(ui->wG2,&LayerEditGrid::clicked,this,&DialogEditGrid::slotItemClicked);


}

DialogEditGrid::~DialogEditGrid()
{
    delete ui;
}

void DialogEditGrid::setObj(ObjData *obj)
{
    m_obj = obj;

    m_iCount = m_obj->m_dataGrid.iCount;

    ui->wG1->setObj(m_obj);

    ui->wG2->setObj(m_obj);
}



void DialogEditGrid::showEvent(QShowEvent *)
{
    resetSize();

    ui->wG1->setListPic(m_obj->m_dataGrid.listG1);

    refresh();
}

void DialogEditGrid::resizeEvent(QResizeEvent *)
{
    resetSize();
}

void DialogEditGrid::resetSize()
{
//    ui->wG1->setGridCount(m_iCount);

//    ui->wG2->setGridCount(m_iCount);
    ui->wG1Area->setMinimumHeight((float)ui->wG1Area->width()/1080*720);
    ui->wG1Area->setMaximumHeight((float)ui->wG1Area->width()/1080*720);

    ui->wG2Area->setMinimumHeight((float)ui->wG2Area->width()/1080*720);
    ui->wG2Area->setMaximumHeight((float)ui->wG2Area->width()/1080*720);

    ui->wG3Area->setMinimumHeight((float)ui->wG3Area->width()/1080*720);
    ui->wG3Area->setMaximumHeight((float)ui->wG3Area->width()/1080*720);


}

void DialogEditGrid::on_btnG1SetListPic_clicked()
{
    QStringList listFile =QFileDialog::getOpenFileNames(this,QStringLiteral("選擇檔案"),
                                                        QApplication::applicationDirPath()+"/../",
                                                        "*.png *.jpg *jpeg");


    while(listFile.length()<9)
        listFile.append("");

    if(listFile.length()>9)
        listFile = listFile.mid(0,9);

    ui->wG1->setListPic(listFile);

    m_obj->m_dataGrid.listG1 = listFile;

    refresh();

}

void DialogEditGrid::on_btnG1SetPic_clicked()
{
    if(ui->wG1->currentId()<0)
    {
        DialogMsg msg;

        msg.setDialogInfo("請先選擇目標格",QStringList()<<"確認");

        msg.exec();
        return;
    }
    QString sFile =QFileDialog::getOpenFileName(this,QStringLiteral("選擇檔案"),
                                                QApplication::applicationDirPath()+"/../",
                                                "*.png *.jpg *jpeg");



    ui->wG1->setPic(sFile);

    m_obj->m_dataGrid.listG1[ui->wG1->currentId()]= sFile;

    refresh();
}

void DialogEditGrid::slotItemClicked(int )
{
    refresh();
}

void DialogEditGrid::slotG2ItemClicked(int )
{
    refresh();
}

void DialogEditGrid::refresh()
{
    qDebug()<<"refresh";

    if(m_iPreG1Idx ==ui->wG1->currentId() && m_iPreG2Idx == ui->wG2->currentId())
        return ;

    m_iPreG1Idx = ui->wG1->currentId();

    m_iPreG2Idx = ui->wG2->currentId();

    ui->wG2->setListPic(m_obj->m_dataGrid.listG2[ui->wG1->currentId()]);

    QPixmap p(m_obj->m_dataGrid.listG3[ui->wG1->currentId()].at(ui->wG2->currentId()));
    ui->wG3->setPixmap(p.scaledToHeight(ui->wG3->height()));

}

void DialogEditGrid::on_btnG2SetPic_clicked()
{
    if(ui->wG2->currentId()<0)
    {
        DialogMsg msg;

        msg.setDialogInfo("請先選擇目標格",QStringList()<<"確認");

        msg.exec();
        return;
    }
    QString sFile =QFileDialog::getOpenFileName(this,QStringLiteral("選擇檔案"),
                                                QApplication::applicationDirPath()+"/../",
                                                "*.png *.jpg *jpeg");



    ui->wG2->setPic(sFile);

    m_obj->m_dataGrid.listG2[ui->wG1->currentId()][ui->wG2->currentId()]= sFile;

    refresh();
}

void DialogEditGrid::on_btnG2SetListPic_clicked()
{
    QStringList listFile =QFileDialog::getOpenFileNames(this,QStringLiteral("選擇檔案"),
                                                        QApplication::applicationDirPath()+"/../",
                                                        "*.png *.jpg *jpeg");


    while(listFile.length()<9)
        listFile.append("");

    if(listFile.length()>9)
        listFile = listFile.mid(0,9);

    ui->wG2->setListPic(listFile);

    m_obj->m_dataGrid.listG2[ui->wG1->currentId()] = listFile;

    refresh();
}

void DialogEditGrid::on_btnG3SetPic_clicked()
{

    QString sFile =QFileDialog::getOpenFileName(this,QStringLiteral("選擇檔案"),
                                                QApplication::applicationDirPath()+"/../",
                                                "*.png *.jpg *jpeg");



    QPixmap p(sFile);
    ui->wG3->setPixmap(p.scaledToHeight(ui->wG3->height()));

    m_obj->m_dataGrid.listG3[ui->wG1->currentId()][ui->wG2->currentId()] = sFile;


}


void DialogEditGrid::on_btnG1Clear_clicked()
{
    ui->wG1->setPic("",ui->wG1->currentId());
    m_obj->m_dataGrid.listG1[ui->wG1->currentId()]="";
}

void DialogEditGrid::on_btnG2Clear_clicked()
{
    ui->wG2->setPic("",ui->wG2->currentId());
     m_obj->m_dataGrid.listG2[ui->wG1->currentId()][ui->wG2->currentId()]="";
}


void DialogEditGrid::on_btnG3Clear_clicked()
{
    QPixmap p("");
    ui->wG3->setPixmap(p.scaledToHeight(ui->wG3->height()));


    m_obj->m_dataGrid.listG3[ui->wG1->currentId()][ui->wG2->currentId()] = "";

}

void DialogEditGrid::on_btnOk_clicked()
{
    done(1);
}
