#include "snowmainframe.h"
#include "ui_snowmainframe.h"

SnowMainFrame::SnowMainFrame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SnowMainFrame)
{
    ui->setupUi(this);

    const quint8 webInterfaceListenPort = 1280;
    const quint8 clientsListenPort = 8140;
    this->webInterface = new WebInterface(webInterfaceListenPort, this);
    this->commandDispatcher = new CommandDispatcher(clientsListenPort, this);
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
