#include "forceexitcommand.h"

ForceExitCommand::ForceExitCommand()
{
    m_next = nullptr;
}

void ForceExitCommand::execCommmand()
{
    QApplication::quit();
}

void ForceExitCommand::message(QString message)
{
    if(message == CMD_FORCE_EXIT)
    {
        execCommmand();
    }
    else
    {
        if(m_next != nullptr) m_next->message(message);
    }
}
