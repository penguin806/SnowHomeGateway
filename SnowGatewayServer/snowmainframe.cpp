#include "snowmainframe.h"
#include "ui_snowmainframe.h"

SnowMainFrame::SnowMainFrame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SnowMainFrame)
{
    ui->setupUi(this);
}

SnowMainFrame::~SnowMainFrame()
{
    delete ui;
}
