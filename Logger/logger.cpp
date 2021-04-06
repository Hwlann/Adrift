#include "logger.h"
#include "ui_logger.h"

Logger *Logger::m_logger = nullptr;

Logger *Logger::getInstance()
{
    if(m_logger == nullptr){
        m_logger = new Logger();
    }
    return m_logger;
}

Logger::Logger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Logger)
{
    ui->setupUi(this);
    this->setWindowTitle("Logger");
    this->setStyleSheet("background-color: #606060;");
    setWindowFlag(Qt::WindowType::Dialog);
}

Logger::~Logger()
{
    delete ui;
}

void Logger::addLog(Logger::LogLevel logLevel, QString message)
{
    Qt::GlobalColor color;
    switch (logLevel)
    {
        case LogLevel::NONE:
        color = Qt::black;
            break;

        case LogLevel::WARNING:
        color = Qt::yellow;
            break;

        case LogLevel::ERROR:
        color = Qt::red;
            break;
    }
        QString log = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + " : " + message;
        ui->listWidget->addItem(log);
        ui->listWidget->item(ui->listWidget->count()-1)->setForeground(color);
}

