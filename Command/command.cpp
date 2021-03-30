#include "command.h"

Command::Command(QObject *parent) : QObject(parent)
{

}

Command *Command::setNext(Command *next)
{
    this->m_next = next;
    return m_next;
}
