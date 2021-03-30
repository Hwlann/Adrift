#include "admincommand.h"

AdminCommand::AdminCommand()
{
    m_next = nullptr;
}

void AdminCommand::execCommand()
{
    emit executeCommand(COMMAND::ADMIN);
}

void AdminCommand::message(QString message)
{
    if(message != CMD_START_ADMIND)
    {
        if(m_next != nullptr) m_next->message(message);
    }
    else
    {
        execCommand();
    }
}
