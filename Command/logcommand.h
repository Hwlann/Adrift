#ifndef LOGCOMMAND_H
#define LOGCOMMAND_H

#include <QDebug>
#include <QMessageBox>

#include "Command/command.h"
#include "Logger/logger.h"

#define CMD_SHOW_LOGS "show logs"
#define CMD_HIDE_LOGS "hide logs"

class LogCommand : public Command
{
public:
    LogCommand();
    void message(QString message);
    void execCommmand(QString cmd);

signals:

};

#endif // LOGCOMMAND_H
