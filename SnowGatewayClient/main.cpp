#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication clientApp(argc, argv);
    QCoreApplication::setApplicationName("SnowHomeGateway-Client");
    QCoreApplication::setApplicationVersion("0.0.1");
    QCoreApplication::setOrganizationDomain("xuefeng.space");

    return clientApp.exec();
}
