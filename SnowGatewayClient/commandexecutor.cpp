#include "commandexecutor.h"
#include <QDebug>

CommandExecutor::CommandExecutor(QObject *parent) : QObject(parent)
{

}

void CommandExecutor::executeCommandFromServer(QString commandString)
{
    try {
        CommandStructure commandStruct = this->parseCommandString(commandString);
        if(commandStruct.getCommandType() != QString("LED"))
        {
            throw QString("ERROR_UNKOWN_COMMAND_TYPE");
        }

        while (!commandStruct.isCommandBodyEmpty())
        {
            quint8 ledNumber = commandStruct.popIntegerFromCommandBody();
            qDebug() << ledNumber;
#ifdef Q_OS_LINUX
            // Execute embedded linux (arm based) code here...
#endif
        }

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
