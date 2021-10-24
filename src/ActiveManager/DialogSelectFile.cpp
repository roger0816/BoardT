#include "DialogSelectFile.h"
#include "ui_DialogSelectFile.h"

DialogSelectFile::DialogSelectFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSelectFile)
{
    ui->setupUi(this);

    setWindowTitle("請選擇檔案與排列順序");

    m_model = new QStandardItemModel(this);

    ui->listView->setModel(m_model);

    ui->listView->setSpacing(5);



    /**for test
    QStringList list;

    for(int i=1;i<5;i++)
    {
        list<<"C:/work/q_project/Tfri/data/clip/"+QString::number(i)+"_0_0.png";

        list<<"C:/work/q_project/Tfri/data/clip/"+QString::number(i)+"_0_1.png";

        list<<"C:/work/q_project/Tfri/data/clip/"+QString::number(i)+"_0_2.png";

        list<<"C:/work/q_project/Tfri/data/clip/"+QString::number(i)+"_0_3.png";

        list<<"C:/work/q_project/Tfri/data/clip/"+QString::number(i)+"_0_4.png";

        list<<"C:/work/q_project/Tfri/data/clip/"+QString::number(i)+"_0_5.png";
    }
    setFileList(list);
    */


}

DialogSelectFile::~DialogSelectFile()
{
    delete ui;
}

void DialogSelectFile::setType(bool bIsPic, QString sFilter)
{
    m_sFilter = sFilter;

    m_bIsPic = bIsPic;

    setPreview(m_bIsPic);
}

void DialogSelectFile::setFileList(QStringList list,QString sPath)
{

    m_listFile = list;

    if(sPath!="")
    {
        for(int i=0;i<m_listFile.length();i++)
        {
            if(!QFileInfo(m_listFile.at(i)).exists() || m_listFile.at(i).split("/").length()<=1)
            {
                m_listFile[i]= sPath+"/"+m_listFile.at(i).split("/").last();
            }
        }
    }
    refreshList();

}

QStringList DialogSelectFile::fileList()
{
    return m_listFile;
}

void DialogSelectFile::setPreview(bool bEnable)
{
    m_bPreView = bEnable;

    ui->wBody->setVisible(m_bPreView);
}

void DialogSelectFile::resizeEvent(QResizeEvent *)
{
    on_listView_pressed(ui->listView->currentIndex());
}

void DialogSelectFile::on_btnOk_clicked()
{
    done(1);
}

void DialogSelectFile::refreshList()
{

    QModelIndex idx = ui->listView->currentIndex();


    m_model->setRowCount(0);

    for(int i=0;i<m_listFile.length();i++)
    {
        // m_model->setRowCount(i+1);

        m_model->appendRow(new QStandardItem(m_listFile.at(i).split("/").last()));
    }

    ui->listView->setCurrentIndex(idx);

    on_listView_pressed(idx);
}

void DialogSelectFile::on_listView_pressed(const QModelIndex &index)
{
    if(index.row()<0 || index.row()>= m_listFile.length())
    {
        ui->lbPic->clear();
        return;
    }

    QPixmap p(m_listFile.at(index.row()));

    ui->lbPic->setPixmap(p.scaledToHeight(ui->lbPic->height()));
}

void DialogSelectFile::on_btnAdd_clicked()
{


    QStringList listSelect =QFileDialog::getOpenFileNames(this,
                                                          QStringLiteral("選擇檔案"),
                                                          QApplication::applicationDirPath()+"/../",
                                                          m_sFilter);




    qDebug()<<"AA : "<<listSelect;
    listSelect.sort();

    qDebug()<<"BB : "<<listSelect;




    //   QString sPic = QFileDialog::getOpenFileName(this,"","../","*.png *.jpg *jpeg");

    int idx = ui->listView->currentIndex().row();

    for(int i=0;i<listSelect.length();i++)
    {
        QString sPic = listSelect.at(i);
        if(sPic!="")
        {

            m_listFile.insert(++idx,sPic);

        }
    }
    refreshList();



    ui->listView->setCurrentIndex(m_model->index(idx,0));

    on_listView_pressed(m_model->index(idx,0));


    bHasChange = true;

}

void DialogSelectFile::on_btnRemove_clicked()
{

    int iRow = ui->listView->currentIndex().row();

    if(iRow>=0 && iRow <m_listFile.length())
    {
        m_listFile.removeAt(iRow);

        refreshList();
    }

    bHasChange = true;
}

void DialogSelectFile::on_btnUp_clicked()
{


    QModelIndex idx = ui->listView->currentIndex();

    int iRow =idx.row();

    if(iRow<=0)
        return;

    m_listFile.move(iRow,iRow-1);

    ui->listView->setCurrentIndex(m_model->index(iRow-1,0));

    refreshList();

    bHasChange = true;

}

void DialogSelectFile::on_btnDown_clicked()
{
    QModelIndex idx = ui->listView->currentIndex();

    int iRow =idx.row();

    if(iRow<0 || iRow >= m_listFile.length()-1)
        return;

    m_listFile.move(iRow,iRow+1);

    ui->listView->setCurrentIndex(m_model->index(iRow+1,0));

    refreshList();

    bHasChange = true;
}
