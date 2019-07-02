#include "webinterface.h"
#include <QTcpSocket>
#include <QDebug>
#include <QTextStream>

WebInterface::WebInterface(quint16 listenPort, QObject *parent) :
    QTcpServer(parent), listenPort(listenPort)
{

}

bool WebInterface::startWebServer()
{
    bool bSuccess;
    bSuccess = this->listen(QHostAddress::Any, this->listenPort);
    return bSuccess;
}

void WebInterface::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *newSocket = new QTcpSocket(this);
    newSocket->setSocketDescriptor(socketDescriptor);
    QObject::connect(newSocket, SIGNAL(readyRead()), this, SLOT(dataFromBrowserReadyToRead()));
    QObject::connect(newSocket, SIGNAL(disconnected()), newSocket, SLOT(deleteLater()));

}

QString WebInterface::parseHttpRequestDataIntoCommand(QByteArray receivedData)
{


}

void WebInterface::dataFromBrowserReadyToRead()
{
    QTcpSocket *socketToRead = (QTcpSocket *)QObject::sender();
    QByteArray receivedData = socketToRead->readAll();
    qDebug() << receivedData;


    QString commandString = this->parseHttpRequestDataIntoCommand(receivedData);

}
