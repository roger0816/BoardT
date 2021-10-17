#ifndef EDITVIDEO_H
#define EDITVIDEO_H

#include <QWidget>
#include "EditBase.h"

namespace Ui {
class EditVideo;
}

class EditVideo : public EditBase
{
    Q_OBJECT

public:
    explicit EditVideo(QWidget *parent = nullptr);
    ~EditVideo();

private:
    Ui::EditVideo *ui;
};

#endif // EDITVIDEO_H
