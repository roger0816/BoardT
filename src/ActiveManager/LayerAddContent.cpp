#include "LayerAddContent.h"
#include "ui_LayerAddContent.h"

LayerAddContent::LayerAddContent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerAddContent)
{
    ui->setupUi(this);

//    m_listBtn<<ui->btnAddText<<ui->btnAddPic<<ui->btnAddVideo<<ui->btnAddBtn
//            <<ui->btnAddMar<<ui->btnAddQr;


//    foreach(QPushButton *btn,m_listBtn)
//    {
//        connect(btn,&QPushButton::clicked,this,&LayerAddContent::slotClicked);
//    }


    m_btns.addButton(ui->btnAddText,ADD_BASIC_TEXT);
    m_btns.addButton(ui->btnAddPic,ADD_BASIC_PIC);
    m_btns.addButton(ui->btnAddVideo,ADD_BASIC_VIDEO);
    m_btns.addButton(ui->btnAddMar,ADD_BASIC_MARQUEE);
    m_btns.addButton(ui->btnAddDateTime,ADD_BASIC_DATETIME);
    m_btns.addButton(ui->btnAddUrl,ADD_BASIC_URL);
     m_btns.addButton(ui->btnAddQr,ADD_BASIC_QR);

    m_btns.addButton(ui->btnAddMedia,ADD_ADV_MEDIA);
    m_btns.addButton(ui->btnAddBtn,ADD_ADV_BUTTON);
    m_btns.addButton(ui->btnAddPixBtn,ADD_ADV_PIX_BUTTON);
    m_btns.addButton(ui->btnAdd964,ADD_ADV_964);
    m_btns.addButton(ui->btnAddPaiter,ADD_ADV_PAINTER);
    m_btns.addButton(ui->btnAddTxtValue,ADD_ADV_TXT);
    m_btns.addButton(ui->btnAddTicket,ADD_ADV_TICKET);
    m_btns.addButton(ui->btnAddOrder,ADD_ADV_ORDER);

    connect(&m_btns,&QButtonGroup::idPressed,this,&LayerAddContent::btnAddClicked);



}

LayerAddContent::~LayerAddContent()
{
    delete ui;
}

void LayerAddContent::slotClicked()
{
//    QPushButton *btn = dynamic_cast<QPushButton*>(sender());

//    emit btnAddClicked(m_listBtn.indexOf(btn));
}

