#ifndef EDITVIDEO_H
#define EDITVIDEO_H

#include <QWidget>
#include <QButtonGroup>
#include "EditBase.h"
#include "DialogSelectFile.h"

namespace Ui {
class EditVideo;
}

class EditVideo : public EditBase
{
    Q_OBJECT

public:
    explicit EditVideo(QWidget *parent = nullptr);
    ~EditVideo();

    void setTarget(ObjData *data) override;

    void refreshTable();

    void clearTable();
private slots:
    void on_btnSetting_clicked();

private:
    Ui::EditVideo *ui;

    QButtonGroup m_btnsRb;
};

#endif // EDITVIDEO_H
