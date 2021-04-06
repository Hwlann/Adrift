#ifndef ADMINCOMMAND_H
#define ADMINCOMMAND_H

#include "Command/command.h"
#include "Command/forceexitcommand.h"
#include <QInputDialog>

#define CMD_START_ADMIND "admin"

class AdminCommand : public Command
{
public:
    AdminCommand();
    void execCommand();
    void message(QString message);
};

#endif // ADMINCOMMAND_H
