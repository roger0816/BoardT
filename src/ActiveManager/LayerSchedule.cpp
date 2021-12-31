#include "LayerSchedule.h"
#include "ui_LayerSchedule.h"

LayerSchedule::LayerSchedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerSchedule)
{
    ui->setupUi(this);

    m_listRb<<ui->rbNone<<ui->rbMuti<<ui->rbOne;



    // ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QFont f;

    f.setPixelSize(14);

    ui->tableWidget->setFont(f);

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableWidget->verticalHeader()->setVisible(false); //隱藏行表頭

    ui->tableWidget->setRowCount(0);

    ui->tableWidget->setColumnCount(3);

    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(240);

}

LayerSchedule::~LayerSchedule()
{
    delete ui;
}


void LayerSchedule::tbAdd(int iIdxPage, QString sTime, int iIsPlay)
{
    int iRow = ui->tableWidget->rowCount();

    ui->tableWidget->setRowCount(iRow+1);

   // ui->tableWidget->setItem(iRow,0,new QTableWidgetItem(QString::number(iRow+1)));

  //  ui->tableWidget->setItem(iRow,1,new QTableWidgetItem(m_sCurrentLayerName));

    QComboBox *comBox = new QComboBox();

    comBox->addItems(CDATA.m_dData.keys());

    comBox->setCurrentIndex(iIdxPage);

    ui->tableWidget->setCellWidget(iRow,0,comBox);

    QTimeEdit *edit = new QTimeEdit;

    edit->setDisplayFormat("hh:mm:ss");

    edit->setTime(QTime::fromString(sTime,"hh:mm:ss"));

 // edit->setTime(QTime(15, 0, 0));
    ui->tableWidget->setCellWidget(iRow,1,edit);


    QComboBox *comBox1 = new QComboBox();
    comBox1->addItem("否");
    comBox1->addItem("是");

    comBox1->setCurrentIndex(iIsPlay);


    ui->tableWidget->setCellWidget(iRow,2,comBox1);
}




void LayerSchedule::showEvent(QShowEvent *)
{

    QTimer::singleShot(50,this,[=]
    {
        read();
      //  readFile(QApplication::applicationDirPath()+"/data/model0/schedule.txt");
    });


}

void LayerSchedule::save()
{

    QSettings conf(CDATA.m_sPath+"/model0.BDM",QSettings::IniFormat);

    conf.setValue("Schedule/Type",rbIndex());

    QStringList listMuti;

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {

        QComboBox *cb=  dynamic_cast<QComboBox*>(ui->tableWidget->cellWidget(i,0));

        QTimeEdit *time=  dynamic_cast<QTimeEdit*>(ui->tableWidget->cellWidget(i,1));


        QComboBox *cb1=  dynamic_cast<QComboBox*>(ui->tableWidget->cellWidget(i,2));

        QString st = QString::number(cb->currentIndex())+"_"+time->time().toString("hh:mm:ss")+"_"+QString::number(cb1->currentIndex());

        listMuti.append(st);
    }

    conf.setValue("Schedule/Muti",listMuti);

    QString sWeek="%1_%2_%3";

    conf.setValue("Schedule/W1",sWeek.arg(QString::number(ui->cbW1->isChecked()))
                  .arg(ui->timeS1->dateTime().toString("hh:mm:ss"))
                  .arg(ui->timeE1->dateTime().toString("hh:mm:ss")));

    conf.setValue("Schedule/W2",sWeek.arg(QString::number(ui->cbW2->isChecked()))
                  .arg(ui->timeS2->dateTime().toString("hh:mm:ss"))
                  .arg(ui->timeE2->dateTime().toString("hh:mm:ss")));

    conf.setValue("Schedule/W3",sWeek.arg(QString::number(ui->cbW3->isChecked()))
                  .arg(ui->timeS3->dateTime().toString("hh:mm:ss"))
                  .arg(ui->timeE3->dateTime().toString("hh:mm:ss")));

    conf.setValue("Schedule/W4",sWeek.arg(QString::number(ui->cbW4->isChecked()))
                  .arg(ui->timeS4->dateTime().toString("hh:mm:ss"))
                  .arg(ui->timeE4->dateTime().toString("hh:mm:ss")));

    conf.setValue("Schedule/W5",sWeek.arg(QString::number(ui->cbW5->isChecked()))
                  .arg(ui->timeS5->dateTime().toString("hh:mm:ss"))
                  .arg(ui->timeE5->dateTime().toString("hh:mm:ss")));

    conf.setValue("Schedule/W6",sWeek.arg(QString::number(ui->cbW6->isChecked()))
                  .arg(ui->timeS6->dateTime().toString("hh:mm:ss"))
                  .arg(ui->timeE6->dateTime().toString("hh:mm:ss")));

    conf.setValue("Schedule/W7",sWeek.arg(QString::number(ui->cbW7->isChecked()))
                  .arg(ui->timeS7->dateTime().toString("hh:mm:ss"))
                  .arg(ui->timeE7->dateTime().toString("hh:mm:ss")));


    QString sSleep="%1_%2_%3";

    conf.setValue("Schedule/Sleep",sSleep.arg(QString::number(ui->cbSleep->isChecked()))
                  .arg(ui->timeSleepS->dateTime().toString("hh:mm:ss"))
                  .arg(ui->timeSleepE->dateTime().toString("hh:mm:ss")));



    conf.sync();

}

void LayerSchedule::read()
{

    QSettings conf(CDATA.m_sPath+"/model0.BDM",QSettings::IniFormat);

    setRbIndex(conf.value("Schedule/Type","0").toInt());

    ui->tableWidget->setRowCount(0);

    QStringList listMuti = conf.value("Schedule/Muti").toStringList();

    for(int i=0;i<listMuti.length();i++)
    {
        QStringList list = listMuti.at(i).split("_");

        if(list.length()>=3)
        tbAdd(list.first().toInt(),list.at(1),list.at(2).toInt());
    }

    QStringList list;

    list = conf.value("Schedule/Sleep").toString().split("_");

    if(list.length()>=3)
    {
        ui->cbSleep->setChecked(list.at(0).toInt());

        ui->timeSleepS->setTime(QTime::fromString(list.at(1),"hh:mm:ss"));

        ui->timeSleepE->setTime(QTime::fromString(list.at(2),"hh:mm:ss"));
    }

    //-----------------

    list = conf.value("Schedule/W1").toString().split("_");

    if(list.length()>=3)
    {
        ui->cbW1->setChecked(list.at(0).toInt());

        ui->timeS1->setTime(QTime::fromString(list.at(1),"hh:mm:ss"));

        ui->timeE1->setTime(QTime::fromString(list.at(2),"hh:mm:ss"));
    }


    list = conf.value("Schedule/W2").toString().split("_");

    if(list.length()>=3)
    {
        ui->cbW2->setChecked(list.at(0).toInt());

        ui->timeS2->setTime(QTime::fromString(list.at(1),"hh:mm:ss"));

        ui->timeE2->setTime(QTime::fromString(list.at(2),"hh:mm:ss"));
    }

    list = conf.value("Schedule/W3").toString().split("_");

    if(list.length()>=3)
    {
        ui->cbW3->setChecked(list.at(0).toInt());

        ui->timeS3->setTime(QTime::fromString(list.at(1),"hh:mm:ss"));

        ui->timeE3->setTime(QTime::fromString(list.at(2),"hh:mm:ss"));
    }

    list = conf.value("Schedule/W4").toString().split("_");

    if(list.length()>=3)
    {
        ui->cbW4->setChecked(list.at(0).toInt());

        ui->timeS4->setTime(QTime::fromString(list.at(1),"hh:mm:ss"));

        ui->timeE4->setTime(QTime::fromString(list.at(2),"hh:mm:ss"));
    }

    list = conf.value("Schedule/W5").toString().split("_");

    if(list.length()>=3)
    {
        ui->cbW5->setChecked(list.at(0).toInt());

        ui->timeS5->setTime(QTime::fromString(list.at(1),"hh:mm:ss"));

        ui->timeE5->setTime(QTime::fromString(list.at(2),"hh:mm:ss"));
    }

    list = conf.value("Schedule/W6").toString().split("_");

    if(list.length()>=3)
    {
        ui->cbW6->setChecked(list.at(0).toInt());

        ui->timeS6->setTime(QTime::fromString(list.at(1),"hh:mm:ss"));

        ui->timeE6->setTime(QTime::fromString(list.at(2),"hh:mm:ss"));
    }

    list = conf.value("Schedule/W7").toString().split("_");

    if(list.length()>=3)
    {
        ui->cbW7->setChecked(list.at(0).toInt());

        ui->timeS7->setTime(QTime::fromString(list.at(1),"hh:mm:ss"));

        ui->timeE7->setTime(QTime::fromString(list.at(2),"hh:mm:ss"));
    }











}

void LayerSchedule::setRbIndex(int idx)
{
    for(int i=0;i<m_listRb.length();i++)
    {
        m_listRb[i]->setChecked(i==idx);
    }
}

int LayerSchedule::rbIndex()
{
    int iRe=0;

    foreach(QRadioButton *btn,m_listRb)
    {
        if(btn->isChecked())
            iRe = m_listRb.indexOf(btn);
    }

    return iRe;
}

void LayerSchedule::slotSelector(QString sName)
{
    m_sCurrentLayerName = sName;
}

void LayerSchedule::on_btnAdd_clicked()
{

//    if(m_sCurrentLayerName=="")
//    {
//        DialogMsg msg;

//        msg.setDialogInfo("請先選擇要新增的版型",QStringList()<<"OK");

//        msg.exec();

//        return ;
//    }

    tbAdd();

    //    QTableWidgetItem *check=new QTableWidgetItem;
    //    check->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
    //    check->setCheckState (Qt::Checked);
    //    ui->tableWidget->setItem(iRow,3,check); //插入复选框
    save();
}

void LayerSchedule::on_btnDel_clicked()
{
    int iRow = ui->tableWidget->currentRow();

    if(iRow<=0 || iRow>= ui->tableWidget->rowCount())
        iRow = ui->tableWidget->rowCount()-1;

    if(iRow>=0 && iRow < ui->tableWidget->rowCount())
    {
        ui->tableWidget->removeRow(iRow);
    }

    save();
}



void LayerSchedule::on_rbNone_clicked()
{
    ui->wSpaceOne->setMinimumHeight(0);
    ui->wSpaceOne->setMaximumHeight(0);

    save();
}


void LayerSchedule::on_rbMuti_clicked()
{
    ui->wSpaceOne->setMinimumHeight(0);
    ui->wSpaceOne->setMaximumHeight(0);

    save();
}


void LayerSchedule::on_rbOne_clicked()
{
    ui->wSpaceOne->setMinimumHeight(350);
    ui->wSpaceOne->setMaximumHeight(350);

    save();
}

