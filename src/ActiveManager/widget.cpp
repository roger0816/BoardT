#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QString def = QApplication::applicationDirPath()+"/data/model0";

    loadModel(def);

    connect(ui->wLayerSelector,&LayerSelector::sendSelectLayer,this,&Widget::slotSelector);

    connect(ui->wDisplay,&DisplayWidget::changeTarget,ui->wEditor,&LayerEditor::setTarget);

    connect(ui->wEditor,&LayerEditor::callUpdate,ui->wDisplay,&DisplayWidget::refreshItem);

    connect(ui->wEditor,&LayerEditor::callRaise,ui->wDisplay,&DisplayWidget::raiseItem);

    connect(ui->wEditor,&LayerEditor::callRename,ui->wDisplay,&DisplayWidget::renameItem);

    connect(ui->wEditor,&LayerEditor::callDelete,ui->wDisplay,&DisplayWidget::deleteItem);

    connect(ui->wAdd,&LayerAddContent::btnAddClicked,ui->wDisplay,&DisplayWidget::addItem);

    ui->wStackWork->setCurrentWidget(ui->page0);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::loadModel(QString sPath)
{

    if(QDir().exists(sPath))
    {
        CDATA.readModel(sPath);

        ui->lbModel->setText(sPath.split("/").last());
    }
    else
    {
        qDebug()<<"model no found : "<<sPath;
    }


    refreshSelector();
}



void Widget::on_btnSelectModel_clicked()
{
    QString sPath = QFileDialog::getOpenFileName(this,"選擇模組",QApplication::applicationDirPath()+"/data","*.BDM");

    QStringList listTmp = sPath.split("/");

    listTmp.pop_back();


    loadModel(listTmp.join("/"));

}

void Widget::on_btnAddModel_clicked()
{
    LayerNewModel dialog;

    dialog.setPath("新增模組",QApplication::applicationDirPath()+"/data/");

    int i =dialog.exec();

    if(i==1)
    {
        QString sTarget =dialog.m_sModelPath;

        QDir().mkdir(sTarget);

        QSettings conf(sTarget+"/"+sTarget.split("/").last()+".BDM",QSettings::IniFormat);

        conf.setValue("Base/default","Default");

        conf.sync();

        QString defLayer = sTarget+"/Default";

        QDir().mkdir(defLayer);

        QSettings def(defLayer+"/Default.BDT",QSettings::IniFormat);

        def.setValue("Base/resumeTimer",15);

        def.sync();

        loadModel(sTarget);
    }
}

void Widget::slotSelector(QString sName)
{
    ui->wStackWork->setCurrentWidget(ui->wWork);

    ui->wDisplay->setLayer(CDATA.m_sPath+"/"+sName);

    ui->wDisplay->setEdit(true);
}

void Widget::refreshSelector()
{
    QStringList listKey = CDATA.m_dData.keys();


    DisplayWidget w;

    QMap <QString , QPixmap> dPix;

    for(int i=0;i<listKey.length();i++)
    {
        dPix.insert(listKey[i], w.setLayer(CDATA.m_dData[listKey.at(i)]->m_sLayerPath));

    }

    ui->wLayerSelector->setData(dPix);
}

void Widget::on_btnAddLayer_clicked()
{
    LayerNewModel newLay;

    newLay.setPath("新增版型",CDATA.m_sPath);

    int iRe = newLay.exec();

    if(iRe ==1 )
    {
        QString defLayer = newLay.m_sModelPath;

        QDir().mkdir(defLayer);

        QSettings def(defLayer+"/.BDT",QSettings::IniFormat);

        def.setValue("Base/resumeTimer",15);

        def.sync();

        CDATA.addLayer(defLayer);

        refreshSelector();
    }
}

void Widget::on_btnSave_clicked()
{
    DialogMsg msg;

    msg.setDialogInfo("確定要儲存嗎？",QStringList()<<"否"<<"是");

    int iRe = msg.exec();

    if(iRe == 1)
        CDATA.writeModel();
}
