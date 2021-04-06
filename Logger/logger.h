#ifndef LOGGER_H
#define LOGGER_H

#include <QWidget>
#include <QDateTime>
#include <QThread>

namespace Ui {
class Logger;
}

class Logger : public QWidget
{
    Q_OBJECT

public:
    enum LogLevel{
        NONE,
        WARNING,
        ERROR
    };
    static Logger *getInstance();
    ~Logger();    
    void addLog(LogLevel logLevel, QString message);

private:
    static Logger *m_logger;
    explicit Logger(QWidget *parent = nullptr);
    Ui::Logger *ui;
};

#endif // LOGGER_H
