#include "commanddispatcher.h"

CommandDispatcher::CommandDispatcher(quint16 clientPort, QObject *parent) :
    QUdpSocket(parent), clientPort(clientPort)
{

}

void CommandDispatcher::sendCommandToClients(QString commandString)
{
    QByteArray commandStringRawData = commandString.toUtf8();
    this->writeDatagram(commandStringRawData.data(),
                        QHostAddress::Broadcast,
                        clientPort);
}
