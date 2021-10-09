#include "ItemBaseObj.h"

ItemBaseObj::ItemBaseObj(QWidget *parent) : QWidget(parent)
{

}

void ItemBaseObj::setData(ObjData *obj)
{
    m_obj = obj;


    init();
    updateItem();
}

QString ItemBaseObj::getStyleSheetRgba(QString st)
{

    st = st.replace("#","");

    while(st.length()<8)
        st+="f";

    QColor bg;

    bool b;
    bg.setRed(st.mid(0,2).toInt(&b,16));

    bg.setGreen(st.mid(2,2).toInt(&b,16));

    bg.setBlue(st.mid(4,2).toInt(&b,16));

    bg.setAlpha(st.mid(6,2).toInt(&b,16));

    QString style = "rgba(%1, %2, %3,%4);";

   return style.arg(bg.red()).arg(bg.green()).arg(bg.blue()).arg(bg.alpha());
}
