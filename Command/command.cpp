#include "command.h"

Command::Command(QObject *parent) : QObject(parent)
{

}

void Command::message(QString cmd)
{
    qDebug() << cmd;
}

Command *Command::setNext(Command *next)
{
    this->m_next = next;
    return m_next;
}
