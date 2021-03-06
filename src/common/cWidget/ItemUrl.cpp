#include "ItemUrl.h"
#include "ui_ItemUrl.h"

ItemUrl::ItemUrl(QWidget *parent) :
    ItemBaseObj(parent),
    ui(new Ui::ItemUrl)
{
    ui->setupUi(this);
#ifdef WEB
    m_view = new QWebView(this);
#else
    m_view = new QLabel(this);
    m_view->setText("Url");
#endif
}

ItemUrl::~ItemUrl()
{
    delete ui;
}



void ItemUrl::updateItem()
{
    if(m_obj==nullptr)
        return;

#ifdef WEB
    m_view->load(QUrl(m_obj->m_data[Url::source].toString()));
#else
  //  m_view->show();
#endif

}

void ItemUrl::reSetSize()
{
   m_view->resize(size());
}
