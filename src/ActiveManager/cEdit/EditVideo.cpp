#include "EditVideo.h"
#include "ui_EditVideo.h"

EditVideo::EditVideo(QWidget *parent) :
    EditBase(parent),
    ui(new Ui::EditVideo)
{
    ui->setupUi(this);
}

EditVideo::~EditVideo()
{
    delete ui;
}
