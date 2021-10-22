#ifndef ITEMURL_H
#define ITEMURL_H

#include <QWidget>
#include <QLabel>
#include "ItemBaseObj.h"
#include <QResizeEvent>
#ifdef WEB
#include <QWebView>
#endif
namespace Ui {
class ItemUrl;
}

class ItemUrl : public ItemBaseObj
{
    Q_OBJECT

public:
    explicit ItemUrl(QWidget *parent = nullptr);
    ~ItemUrl();


    void updateItem()override;

    void loadUrl(QString sUrl);
private:

#ifdef WEB
     QWebView *m_view;
#else
    QLabel *m_view;
#endif

    void reSetSize() override;

private:
    Ui::ItemUrl *ui;
};

#endif // ITEMURL_H
