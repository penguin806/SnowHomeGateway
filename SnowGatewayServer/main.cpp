#include "snowmainframe.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication serverApp(argc, argv);
    QApplication::setApplicationName("SnowHomeGateway-Server");
    QApplication::setApplicationVersion("0.1.0");
    QApplication::setOrganizationDomain("xuefeng.space");

    SnowMainFrame mainFrame;
    mainFrame.show();

    return serverApp.exec();
}
