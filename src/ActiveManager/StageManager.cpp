#include "StageManager.h"
#include "ui_StageManager.h"

StageManager::StageManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageManager)
{
    ui->setupUi(this);

    ui->btnUpload->setData(QStringList()<<":/button/folder-html-icon.png","上傳專案");

    ui->btnDownload->setData(QStringList()<<":/button/folder-downloads-icon.png","下載專案");


    m_lay = new QGridLayout;

    addData(QDir(QApplication::applicationDirPath()+"/data").entryList(QDir::Dirs | QDir::NoDotAndDotDot),false);

    if(m_listBtn.buttons().length()>0)
        m_listBtn.buttons()[0]->setChecked(true);
}

StageManager::~StageManager()
{
    delete ui;
}

void StageManager::on_btnNew_clicked()
{

    DialogMsg msg;

    msg.setInput("新增專案\n\n請設定名稱","",QStringList()<<"取消"<<"確定");

    if(msg.exec()==0)
        return;

    QString sName = msg.getInput();
    //qDeleteAll(ui->wSpace->children());

    addData(QStringList()<<sName);



}

void StageManager::addData(QStringList list, bool bNew)
{
    for(int i=0;i<list.length();i++)
    {

        QCheckBox * t = new QCheckBox();

        QFont font;

        font.setPixelSize(22);

        font.setBold(true);

        t->setFont(font);

        t->setMinimumSize(QSize(120,30));

        t->setMaximumSize(QSize(120,30));

        m_listBtn.addButton(t,m_listBtn.buttons().length());



        m_listKey.append(list.at(i));

        if(bNew)
            CDATA.createModel(list.at(i));
    }

    delete  m_lay;

    m_lay = new QGridLayout;


    for(int i=0;i<m_listBtn.buttons().length();i++)
    {
        m_lay->addWidget(m_listBtn.buttons()[i],i/5,i%5);

        m_listBtn.buttons()[i]->setText(m_listKey.at(i));
    }

    ui->wSpace->setLayout(m_lay);



}

void StageManager::on_btnDelete_clicked()
{

    if(m_listBtn.checkedId()<0)
    {
        DialogMsg msg;

        msg.setDialogInfo("請先選擇目標",QStringList()<<"OK");

        msg.exec();


        return ;
    }


    DialogMsg msg2;

    msg2.setDialogInfo("確定要刪除 '"+m_listKey.at(m_listBtn.checkedId())+"' 嗎?",QStringList()<<"取消"<<"確認");

    if(msg2.exec()==0)
        return;


    m_listKey.removeAt(m_listBtn.checkedId());

    m_listBtn.removeButton(m_listBtn.button(m_listBtn.checkedId()));


    delete  m_lay;

    m_lay = new QGridLayout;


    for(int i=0;i<m_listBtn.buttons().length();i++)
    {
        m_lay->addWidget(m_listBtn.buttons()[i],i/5,i%5);

        m_listBtn.buttons()[i]->setText(m_listKey.at(i));
    }

    ui->wSpace->setLayout(m_lay);



}

void StageManager::on_btnEdit_clicked()
{
    if(m_listBtn.checkedId()<0)
    {
        DialogMsg msg;

        msg.setDialogInfo("請先選擇目標",QStringList()<<"OK");

        msg.exec();


        return ;
    }

    QString sPath = QApplication::applicationDirPath()+"/data/"+m_listKey.at(m_listBtn.checkedId());

    emit sendSelectModel(sPath);

    // loadModel(QApplication::applicationDirPath()+"/data/"+m_listKey.at(m_listBtn.checkedId()));


}
