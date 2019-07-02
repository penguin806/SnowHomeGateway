#include "snowmainframe.h"
#include "ui_snowmainframe.h"

SnowMainFrame::SnowMainFrame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SnowMainFrame)
{
    ui->setupUi(this);
    this->webInterface = new WebInterface(12800, this);
    this->webInterface->startWebServer();
}

SnowMainFrame::~SnowMainFrame()
{
    delete ui;
}
