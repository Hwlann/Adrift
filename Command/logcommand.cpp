#include "logcommand.h"

LogCommand::LogCommand()
{
    m_next = nullptr;
}

void LogCommand::message(QString message)
{
    qDebug() << __PRETTY_FUNCTION__;
    if(message == CMD_SHOW_LOGS)
    {
        execCommmand(true);
    }
    else if(message == CMD_HIDE_LOGS)
    {
        execCommmand(false);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Unknown Command");
        msgBox.exec();
    }
}

void LogCommand::execCommmand(bool loggerVisibility)
{
    Logger::getInstance()->setVisible(loggerVisibility);
    Logger::getInstance()->addLog(Logger::LogLevel::NONE, "EFM LOGGER");
    Logger::getInstance()->addLog(Logger::LogLevel::WARNING, "EFM LOGGER");
    Logger::getInstance()->addLog(Logger::LogLevel::ERROR, "EFM LOGGER");
}
