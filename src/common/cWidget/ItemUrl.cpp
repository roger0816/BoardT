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
    m_view = new QWidget(this);
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
    m_view->load(QUrl(m_obj->m_data[Url::source]));
#endif
    m_view->show();

}

void ItemUrl::reSetSize()
{
   m_view->resize(size());
}
