#ifndef COMMANDDISPATCHER_H
#define COMMANDDISPATCHER_H
#include <QUdpSocket>

class CommandDispatcher : public QUdpSocket
{
    Q_OBJECT

public:
    CommandDispatcher(quint16 clientPort, QObject *parent = nullptr);

public slots:
    void sendCommandToClients(QString commandString);

private:
    quint16 clientPort;
};

#endif // COMMANDDISPATCHER_H
