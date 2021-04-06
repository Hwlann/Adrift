#ifndef FORCEPATH_H
#define FORCEPATH_H

#include "Command/command.h"

#define CMD_FORCE_PATH "path="

class ForcePath : public Command
{
public:
    ForcePath();
    void execCommand();
    void message(QString message);
private:
    QString m_cmd = CMD_FORCE_PATH;
};

#endif // FORCEPATH_H
