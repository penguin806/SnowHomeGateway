#include "commandexecutor.h"
#include <QDebug>

#ifdef Q_OS_LINUX
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#endif

CommandExecutor::CommandExecutor(QObject *parent) : QObject(parent)
{

}

void CommandExecutor::executeCommandFromServer(QString commandString)
{
    try {
        CommandStructure commandStruct = this->parseCommandString(commandString);
        if(commandStruct.getCommandType() != QString("LED"))
        {
            throw QString("ERROR_UNKNOWN_COMMAND_TYPE");
        }

        int controlBits = 0x00f; // Binary: 00000000
        while (!commandStruct.isCommandBodyEmpty())
        {
            quint8 ledNumber = commandStruct.popIntegerFromCommandBody();
            controlBits |= (1 << (ledNumber-1));
            qDebug() << controlBits;
        }

#ifdef Q_OS_LINUX
        // Execute code for CVT4418 mathine (arm based embedded linux) here...

        int fileDescriptor = open("/dev/cled_ctl",O_RDWR);
        if(fileDescriptor == -1)
        {
            throw QString("ERROR_OPEN_DEVICE_FAILED");
        }
        ioctl(fileDescriptor, 0, controlBits);
        close(fileDescriptor);
#endif

    } catch (QString errorString) {
        qDebug() << errorString;
    }
}

CommandStructure CommandExecutor::parseCommandString(QString commandString)
{
    CommandStructure commandStruct;
    QStringList commandElements = commandString.split('-');
    if(commandElements.size() != 3)
    {
        throw QString("ERROR_COMMAND_STRING_INVALID");
    }

    commandStruct.setCommandType(commandElements.at(0));

    quint8 checkBit = commandElements.at(1).toInt();
    quint8 commandBitSum = 0;
    QString commandStringBody = commandElements.at(2);
    for(int i=0; i<commandStringBody.length(); i++)
    {
        commandStruct.pushIntegerIntoCommandBody(commandStringBody.at(i).digitValue());
        commandBitSum += commandStringBody.at(i).digitValue();
    }

    if(commandBitSum % 10 != checkBit)
    {
        throw QString("ERROR_COMMAND_INTEGRITY_CHECK_FAILED");
    }

    return commandStruct;
}
