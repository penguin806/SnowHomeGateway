#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H

#include <QObject>
#include "commandstructure.h"

class CommandExecutor : public QObject
{
    Q_OBJECT
public:
    explicit CommandExecutor(QObject *parent = nullptr);

public slots:
    void executeCommandFromServer(QString commandString);
    CommandStructure parseCommandString(QString commandString);

protected:

};

#endif // COMMANDEXECUTOR_H
