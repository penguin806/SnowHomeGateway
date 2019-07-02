#include "snowmainframe.h"
#include "ui_snowmainframe.h"

SnowMainFrame::SnowMainFrame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SnowMainFrame)
{
    ui->setupUi(this);
    this->webInterface = new WebInterface(1280, this);
    this->commandDispatcher = new CommandDispatcher(8140, this);
    QObject::connect(this->webInterface, SIGNAL(receivedCommandFromWebInterface(QString)),
                     this->commandDispatcher, SLOT(sendCommandToClients(QString)));

    this->webInterface->startWebServer();
}

SnowMainFrame::~SnowMainFrame()
{
    this->webInterface->deleteLater();
    this->commandDispatcher->deleteLater();
    delete ui;
}
