#include "webinterface.h"
#include <QTcpSocket>
#include <QDebug>
#include <QTextStream>
#include <QRegularExpression>

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
    //    Test request data:
    //    GET /ledControl?led1=on&led2=on&led8=on HTTP/1.1
    //    Host: localhost:12800
    //    User-Agent: Mozilla/5.0 (Windows NT 6.3; Win64; x64; rv:67.0) Gecko/20100101 Firefox/67.0
    //    Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
    //    Accept-Language: en-US,en;q=0.5
    //    Accept-Encoding: gzip, deflate
    //    Referer: http://localhost:63342/Web/ControlPanel.html?_ijt=eqq64nf5her7m3b7k7rkq4irm2
    //    Connection: keep-alive
    //    Cookie: vchideactivationmsg=1; vchideactivationmsg_vc11=4.11.2.1; Idea-5a669e39=10aeb262-1114-42f7-ac42-ff4d9ca301e1; Webstorm-3d0489d2=8d194f99-0d68-400f-8cd0-c15e22370e0c
    //    Upgrade-Insecure-Requests:

    QTextStream receivedDataStream(receivedData, QIODevice::ReadOnly);
    try
    {
        QString startLine = receivedDataStream.readLine();
        if(startLine.isEmpty())
        {
            throw QString("ERROR-EMPTY_REQUEST");
        }

        QRegularExpression startLineRegExp("^(\\w+)\\s{1}(.*?)\\?(.*?)\\s{1}(.*)$");
        // GET /ledControl?led1=on&led2=on&led8=on HTTP/1.1
        // MatchGroup 1: GET                        (HttpMethod)
        // MatchGroup 2: /ledControl                (RequestTarget)
        // MatchGroup 3: led1=on&led2=on&led8=on    (QueryString)
        // MatchGroup 4: HTTP/1.1                   (HttpVersion)
        QRegularExpressionMatch match = startLineRegExp.match(startLine);
        if(!match.hasMatch() || 0 == match.capturedLength(3))
        {
            throw QString("ERROR-INVALID_START_LINE");
        }

        QString queryString = match.captured(3);
        QRegularExpression queryStringRegExp("led([1-8])=on");
        // led1=on&led2=on&led8=on
        QRegularExpressionMatchIterator matchIterator =
                queryStringRegExp.globalMatch(queryString);

        // COMMAND FORMAT DEFINATION:
        // <Type>-<Check Bit>-<Command Body>
        const QString commandType = "LED";
        int checkBit = 0;
        QString commandBody = "";

        while(matchIterator.hasNext())
        {
            match = matchIterator.next();
            commandBody += match.captured(1);
            checkBit += match.captured(1).toInt();
        }

        return commandType + '-' + QString::number(checkBit % 10)
                + '-' + commandBody;
    }
    catch (QString errorString)
    {
        return errorString;
    }
}

void WebInterface::dataFromBrowserReadyToRead()
{
    QTcpSocket *socketToRead = (QTcpSocket *)QObject::sender();
    QByteArray receivedData = socketToRead->readAll();
    qDebug() << receivedData;

    // COMMAND FORMAT DEFINATION:
    // <Type>-<Check Bit>-<Command Body>
    // Example: LED-1-128
    QString commandString = this->parseHttpRequestDataIntoCommand(receivedData);
    qDebug() << commandString;
    emit receivedCommandFromWebInterface(commandString);
}
