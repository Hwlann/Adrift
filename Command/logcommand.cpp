#include "logcommand.h"

LogCommand::LogCommand()
{
    m_next = nullptr;
}

void LogCommand::message(QString message)
{
    //qDebug() << __PRETTY_FUNCTION__;
    if(message == CMD_SHOW_LOGS || message == CMD_HIDE_LOGS)
    {
      execCommmand(message);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Unknown Command");
        msgBox.exec();
    }
}

void LogCommand::execCommmand(QString cmd)
{
    emit executeCommand(COMMAND::SHOW_LOGS, cmd);
}
