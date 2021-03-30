#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow *MainWindow::m_mainWindow = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setupUi();
}

MainWindow *MainWindow::getInstance(QWidget *parent)
{
    if(m_mainWindow == nullptr){
        m_mainWindow = new MainWindow(parent);
    }
    return m_mainWindow;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUi()
{
    this->setFixedWidth(WINDOW_WIDTH);
    this->setFixedHeight(WINDOW_HEIGHT);
    this->setWindowTitle(WINDOW_TITLE);
    ui->btn_startGame->setEnabled(false);
    ui->pushButton->setEnabled(false);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->show();
}

void MainWindow::changeStatusbarText(QString *text)
{
    this->setStatusTip(*text);
}

void MainWindow::changeStartGameBtn(bool enable)
{
    ui->btn_startGame->setEnabled(enable);
}

void MainWindow::on_lineEdit_returnPressed()
{
    emit commandCommit(ui->lineEdit->text());
}

void MainWindow::on_btn_register_clicked()
{
    QDesktopServices::openUrl(QUrl(REGISTER_URL));
}

void MainWindow::on_pushButton_clicked()
{
    emit login(ui->le_id->text(), ui->le_password->text());
    emit getPlayerName(ui->le_id->text());
}

void MainWindow::changeLoginVisibilty()
{
    if(ui->le_id->text() != NULL && ui->le_password->text() != NULL) ui->pushButton->setEnabled(true);
    else ui->pushButton->setEnabled(false);
}

void MainWindow::on_le_id_textEdited()
{
    changeLoginVisibilty();
}

void MainWindow::on_le_password_textEdited()
{
    changeLoginVisibilty();
}

void MainWindow::on_btn_startGame_clicked()
{
    emit startGame();
}

void MainWindow::mousePressEvent(QMouseEvent *evt)
{
    oldPos = evt->globalPos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *evt)
{
    const QPoint delta = evt->globalPos() - oldPos;
    if (locked)
        // if locked, ignore delta on y axis, stay at the top
        move(x()+delta.x(), y());
    else
        move(x()+delta.x(), y()+delta.y());
    oldPos = evt->globalPos();
}
