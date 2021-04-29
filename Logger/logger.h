#ifndef LOGGER_H
#define LOGGER_H

#include <QWidget>
#include <QDateTime>
#include <QMouseEvent>

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

protected:
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);

private:
    static Logger *m_logger;
    explicit Logger(QWidget *parent = nullptr);
    Ui::Logger *ui;

    QPoint oldPos;
    bool locked = false;
};

#endif // LOGGER_H
