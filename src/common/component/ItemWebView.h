#ifndef ITEMWEBVIEW_H
#define ITEMWEBVIEW_H

#include "ItemBase.h"
#include "Global.h"

#ifdef WEB
#include <QtWebKitWidgets>

class ItemWebView : public ItemBase
{
    Q_OBJECT
public:
    explicit ItemWebView(QWidget *parent = nullptr);

    bool init() override;

    void loadUrl(QString sUrl);

    QWebView *m_view;

    QStringList m_listUrl;
    void resizeEvent(QResizeEvent *) override;
signals:

public slots:
};

#else

class ItemWebView : public ItemBase
{
    Q_OBJECT
public:
    explicit ItemWebView(QWidget *parent = nullptr):ItemBase(parent){}

    bool init() override {return true;}

    void loadUrl(QString sUrl){}

    QStringList m_listUrl;

signals:

public slots:
};

#endif

#endif // ITEMWEBVIEW_H
