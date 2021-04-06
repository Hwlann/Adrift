#ifndef FORCEEXITCOMMAND_H
#define FORCEEXITCOMMAND_H

#include "Command/command.h"
#include "Command/logcommand.h"
#include <QObject>
#include <QApplication>

#define CMD_FORCE_EXIT "exit"

class ForceExitCommand : public Command
{
public:
    ForceExitCommand();
    void execCommmand();
    void message(QString message);
};

#endif // FORCEEXITCOMMAND_H
