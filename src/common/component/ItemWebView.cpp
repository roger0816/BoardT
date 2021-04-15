#include "ItemWebView.h"



#ifdef WEB

ItemWebView::ItemWebView(QWidget *parent) : ItemBase(parent)
{
    m_view = new QWebView(this);
}

bool ItemWebView::init()
{

    bool b = false;

    QFileInfoList list = QDir(m_sPath).entryInfoList(QStringList()<<"*.txt");

    if(list.length()>0)
    {
        QFile file(list.first().filePath());

        if(file.open(QIODevice::ReadOnly))
        {


            QByteArray byte = file.readAll();

            QString sTmp(byte);

            sTmp.replace(" ","");

            m_listUrl = sTmp.split("\n");

            if(m_listUrl.length()>0)
            {
                //m_view->load(QUrl("https://tw.news.yahoo.com/weather/"));
                 loadUrl(m_listUrl.first());

                b = true;
            }

        }

    }



    return b;
}

void ItemWebView::loadUrl(QString sUrl)
{
    QTimer::singleShot(100,this,[=]
    {
        m_view->load(QUrl(sUrl));
       m_view->show();

       });



}

void ItemWebView::resizeEvent(QResizeEvent *)
{

    m_view->resize(size());

}

#endif
