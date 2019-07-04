#ifndef COMMANDRECEIVER_H
#define COMMANDRECEIVER_H

#include <QUdpSocket>

class CommandReceiver : public QUdpSocket
{
    Q_OBJECT
public:
    explicit CommandReceiver(quint16 listenPort, QObject *parent = nullptr);
    bool startListening();

signals:
    void receivedCommandFromServer(QString commandString);

private slots:
    void dataFromServerReadyRead();

private:
    const quint16 listenPort;
};

#endif // COMMANDRECEIVER_H
