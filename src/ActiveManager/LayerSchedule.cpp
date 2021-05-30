#include "LayerSchedule.h"
#include "ui_LayerSchedule.h"

LayerSchedule::LayerSchedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerSchedule)
{
    ui->setupUi(this);

    // ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QFont f;

    f.setPixelSize(14);

    ui->tableWidget->setFont(f);

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableWidget->verticalHeader()->setVisible(false); //隱藏行表頭

    ui->tableWidget->setRowCount(0);
}

LayerSchedule::~LayerSchedule()
{
    delete ui;
}

void LayerSchedule::setData(QStringList list, int iRow)
{
    if(list.length()< ui->tableWidget->columnCount())
    {
        return ;
    }


    if(iRow >= ui->tableWidget->rowCount())
    {
        ui->tableWidget->setRowCount(iRow+1);
    }


    ui->tableWidget->setItem(iRow,0,new QTableWidgetItem(list.at(0)));

    ui->tableWidget->setItem(iRow,1,new QTableWidgetItem(list.at(1)));


    QTimeEdit *edit = new QTimeEdit;

    edit->setDisplayFormat("hh:mm:ss");

    edit->setTime(QTime::fromString(list.at(2),"hh:mm:ss"));


    ui->tableWidget->setCellWidget(iRow,2,edit);


    QComboBox *comBox = new QComboBox();
    comBox->addItem("否");
    comBox->addItem("是");

    comBox->setCurrentIndex(list.at(3).toInt());
    ui->tableWidget->setCellWidget(iRow,3,comBox);

    //    QTableWidgetItem *check=new QTableWidgetItem;
    //    check->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
    //    check->setCheckState (Qt::Checked);
    //    ui->tableWidget->setItem(iRow,3,check); //插入复选框

    QComboBox *comBox2 = new QComboBox();
    comBox2->addItem("否");
    comBox2->addItem("是");

    ui->tableWidget->setCellWidget(iRow,4,comBox2);
}

void LayerSchedule::writeFile(QString sFileName)
{
    QFile f(sFileName);

    f.open(QIODevice::WriteOnly);

    QStringList list;

    list.append(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

    for(int i =0 ;i<ui->tableWidget->rowCount();i++)
    {


        QString str = ui->tableWidget->item(i,0)->text()+",";

        str += ui->tableWidget->item(i,1)->text()+",";

        QWidget *wTime=ui->tableWidget->cellWidget(i,2);

        QTimeEdit *edit = dynamic_cast<QTimeEdit*>(wTime);

        str += edit->time().toString("hh:mm:ss")+",";


        QWidget *w1=ui->tableWidget->cellWidget(i,3);

        QComboBox *cb1 = dynamic_cast<QComboBox*>(w1);

        str += QString::number(cb1->currentIndex())+",";


        QWidget *w2=ui->tableWidget->cellWidget(i,4);

        QComboBox *cb2 = dynamic_cast<QComboBox*>(w2);

        str += QString::number(cb2->currentIndex());

        list.append(str);

        qDebug()<<str;

    }


    QByteArray data;

    data.append(list.join("\n"));

    f.write(data);

    f.close();





}

void LayerSchedule::readFile(QString sFileName)
{
    QFile f(sFileName);

    f.open(QIODevice::ReadOnly);

    QStringList list;

    QString st(f.readAll());

    list = st.split("\n");

    ui->tableWidget->setRowCount(list.count());

    for(int i=0;i<list.length();i++)
    {
        setData(list.at(i).split(","),i);

    }



}

void LayerSchedule::showEvent(QShowEvent *)
{

    QTimer::singleShot(50,this,[=]
    {
        readFile(QApplication::applicationDirPath()+"/data/model0/schedule.txt");
    });


}

void LayerSchedule::slotSelector(QString sName)
{
    m_sCurrentLayerName = sName;
}

void LayerSchedule::on_btnAdd_clicked()
{
    if(m_sCurrentLayerName=="")
    {
        DialogMsg msg;

        msg.setDialogInfo("請先選擇要新增的版型",QStringList()<<"OK");

        msg.exec();

        return ;
    }

    int iRow = ui->tableWidget->rowCount();

    ui->tableWidget->setRowCount(iRow+1);

    ui->tableWidget->setItem(iRow,0,new QTableWidgetItem(QString::number(iRow+1)));

    ui->tableWidget->setItem(iRow,1,new QTableWidgetItem(m_sCurrentLayerName));


    QTimeEdit *edit = new QTimeEdit;

    edit->setDisplayFormat("hh:mm:ss");

    ui->tableWidget->setCellWidget(iRow,2,edit);


    QComboBox *comBox = new QComboBox();
    comBox->addItem("否");
    comBox->addItem("是");

    ui->tableWidget->setCellWidget(iRow,3,comBox);

    //    QTableWidgetItem *check=new QTableWidgetItem;
    //    check->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
    //    check->setCheckState (Qt::Checked);
    //    ui->tableWidget->setItem(iRow,3,check); //插入复选框

    QComboBox *comBox2 = new QComboBox();
    comBox2->addItem("否");
    comBox2->addItem("是");

    ui->tableWidget->setCellWidget(iRow,4,comBox2);
}

void LayerSchedule::on_btnDel_clicked()
{
    int iRow = ui->tableWidget->currentRow();

    if(iRow>=0 && iRow < ui->tableWidget->rowCount())
    {
        ui->tableWidget->removeRow(iRow);
    }
}

void LayerSchedule::saveSchedule()
{


//    DialogMsg msg;

//    msg.setDialogInfo("確定儲存嗎？",QStringList()<<"否"<<"是");

//    int iRe = msg.exec();


//    if(iRe ==1)
        writeFile(QApplication::applicationDirPath()+"/data/model0/schedule.txt");
}
