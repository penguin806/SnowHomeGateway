#ifndef COMMANDSTRUCTURE_H
#define COMMANDSTRUCTURE_H
#include <QString>
#include <QList>

class CommandStructure
{
public:
    CommandStructure()
    {

    }

    void setCommandType(QString commandType)
    {
        this->commandType = commandType;
    }

    QString getCommandType()
    {
        return this->commandType;
    }

    void pushIntegerIntoCommandBody(quint8 ledNumber)
    {
        this->commandBody.append(ledNumber);
    }

    quint8 popIntegerFromCommandBody()
    {
        return this->commandBody.takeFirst();
    }

    bool isCommandBodyEmpty()
    {
        return this->commandBody.size() > 0 ? false : true;
    }

private:
    QString commandType;
    QList<quint8> commandBody;
};

#endif // COMMANDSTRUCTURE_H
