#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QDebug>

class Command : public QObject
{
    Q_OBJECT
public:
    explicit Command(QObject *parent = nullptr);
    enum COMMAND {
        SHOW_LOGS,
        SHOW_FPS,
        ADMIN,
        FEXIT
    };

    virtual void message(QString message) = 0;
    Command *setNext(Command *cmd);


protected:
    QString m_command;
    Command *m_next;

signals:
    void executeCommand(COMMAND cmd);

};

#endif // COMMAND_H
