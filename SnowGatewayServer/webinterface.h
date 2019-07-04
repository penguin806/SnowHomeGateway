#ifndef WEBINTERFACE_H
#define WEBINTERFACE_H

#include <QTcpServer>

class WebInterface : public QTcpServer
{
    Q_OBJECT
public:
    explicit WebInterface(quint16 listenPort, QObject *parent = nullptr);
    bool startWebServer();

signals:
    void receivedCommandFromWebInterface(QString commandString);

protected:
    //@Override
    virtual void incomingConnection(qintptr socketDescriptor);
    QString parseHttpRequestDataIntoCommand(QByteArray receivedData);

private slots:
    void dataFromBrowserReadyToRead();

private:
    const quint16 listenPort;
};

#endif // WEBINTERFACE_H
