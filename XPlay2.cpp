#include "XPlay2.h"
#include "ui_XPlay2.h"

XPlay2::XPlay2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::XPlay2)
{
    ui->setupUi(this);
}

XPlay2::~XPlay2()
{
    delete ui;
}

XVideoWidget* XPlay2::getVideo()
{
    return ui->video;
}

