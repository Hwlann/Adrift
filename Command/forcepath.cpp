#include "forcepath.h"

ForcePath::ForcePath()
{
    m_next = nullptr;
}

void ForcePath::execCommand()
{

}

void ForcePath::message(QString message)
{
    if(message.contains(m_cmd) && message.rightRef(m_cmd.size()-1).size() > 0)
    {
        emit executeCommand(COMMAND::PATH, message.remove(0, m_cmd.size()));
    }
    else
    {
        if(m_next != nullptr) m_next->message(message);
    }
}
