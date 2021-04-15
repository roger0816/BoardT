#include "LayerNewModel.h"
#include "ui_LayerNewModel.h"

LayerNewModel::LayerNewModel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LayerNewModel)
{
    ui->setupUi(this);

    QDir dir(QApplication::applicationDirPath()+"/data/layer/");

    setPath(dir.path()+"/");

    ui->btnSelect->hide();
}

LayerNewModel::~LayerNewModel()
{
    delete ui;
}

void LayerNewModel::setPath(QString sPath)
{
    ui->lbPath->setText(sPath);
}

void LayerNewModel::on_btnCancel_clicked()
{
    this->reject();
}

void LayerNewModel::on_btnOk_clicked()
{
    ui->lbMsg->clear();

    QDir d(ui->lbPath->text()+ui->txtName->text().trimmed());


    if(ui->txtName->text().trimmed()=="")
    {
        ui->lbMsg->setText("請輸入樣版名稱");
        return ;
    }


    else if(d.exists())
    {


        ui->lbMsg->setText("樣版已經存在");

       return;

    }

    m_sModelPath = ui->lbPath->text()+ui->txtName->text();

//    QDir d2(ui->lbPath->text());

//    d2.mkdir(ui->txtName->text().trimmed());

    this->done(1);
}

void LayerNewModel::on_btnSelect_clicked()
{


    QString dir = QFileDialog::getExistingDirectory(
                this, tr("選擇樣版存放位置"),
                ui->lbPath->text().trimmed(),
                QFileDialog::ShowDirsOnly
                | QFileDialog::DontResolveSymlinks);


    ui->lbPath->setText(dir+"/");
}
