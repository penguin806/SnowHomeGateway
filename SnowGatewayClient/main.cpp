#include <QCoreApplication>
#include "commandreceiver.h"
#include "commandexecutor.h"

int main(int argc, char *argv[])
{
    QCoreApplication clientApp(argc, argv);
    QCoreApplication::setApplicationName("SnowHomeGateway-Client");
    QCoreApplication::setApplicationVersion("0.1.0");
    QCoreApplication::setOrganizationDomain("xuefeng.space");

    const quint16 listenPort = 8140;
    CommandReceiver commandReceiver(listenPort, &clientApp);
    CommandExecutor commandExecutor(&clientApp);
    QObject::connect(&commandReceiver, SIGNAL(receivedCommandFromServer(QString)),
                     &commandExecutor, SLOT(executeCommandFromServer(QString)));
    commandReceiver.startListening();

    return clientApp.exec();
}
