#include "commandreceiver.h"
#include <QDebug>

CommandReceiver::CommandReceiver(quint16 listenPort, QObject *parent) :
    QUdpSocket(parent), listenPort(listenPort)
{

}

bool CommandReceiver::startListening()
{
    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(dataFromServerReadyRead()));
    return this->bind(QHostAddress::Any, this->listenPort);
}

void CommandReceiver::dataFromServerReadyRead()
{
    QByteArray receiveDataBuffer;
    receiveDataBuffer.resize(this->pendingDatagramSize());

    this->readDatagram(receiveDataBuffer.data(), receiveDataBuffer.size());
    qDebug() << receiveDataBuffer;
    emit receivedCommandFromServer(QString::fromUtf8(receiveDataBuffer));
}
