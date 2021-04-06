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

/************************* CUSTOMS ****************************************/
void MainWindow::setupUi()
{
    this->setFixedWidth(WINDOW_WIDTH);
    this->setFixedHeight(WINDOW_HEIGHT);
    this->setWindowTitle(WINDOW_TITLE);


    m_mutePixmap = new QPixmap(":/img/mute.png");
    m_soundOnPixmap = new QPixmap(":/img/soundOn.png");

    soundIcon = new QIcon(*m_mutePixmap);
    muteIcon = new QIcon(*m_soundOnPixmap);

    ui->btn_play->setEnabled(false);
    ui->btn_login->setEnabled(false);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    setStyleSheets();
    setFont();
    setBackground();
    this->show();
}

void MainWindow::changeStatusbarText(QString *text)
{
    this->setStatusTip(*text);
}

void MainWindow::changeStartGameBtn(bool enable)
{
    ui->btn_play->setEnabled(enable);
}

void MainWindow::clearLineEditCommand(){
    ui->lineEdit->clear();
}


void MainWindow::setStyleSheets()
{
    /****************************** LINE EDIT ******************************/
    ui->le_username->setStyleSheet("* { background-color: rgba(0, 0, 0, 0);"
"                                       font-size: 9px}");

    ui->le_password->setStyleSheet("* { background-color: rgba(0, 0, 0, 0);"
"                                       font-size: 9px}");

    ui->lineEdit->setStyleSheet("* { background-color: rgba(0, 0, 0, 0);"
"                                    font-size: 10px;}"
"                                    color: #000000;");

     /****************************** LABELS ******************************/
    ui->lbl_escape->setStyleSheet("* { background-color: rgba(0, 0, 0, 0);"
"                                      color: #FFFFFF;"
"                                      font-size: 18px;}");

    ui->lbl_markov->setStyleSheet("* { background-color: rgba(0, 0, 0, 0);"
"                                      color: #FFFFFF;"
"                                      font-size: 28px}");

     /****************************** BTN WINDOW ******************************/
    ui->btn_exit->setStyleSheet("* { background-color: rgba(0, 0, 0, 0);"
"                                    color: #FFFFFF;"
"                                    font-size: 8px}");

    ui->btn_reduce->setStyleSheet("* { background-color: rgba(0, 0, 0, 0);"
"                                      color: #FFFFFF;"
"                                      font-size: 8px}");

    ui->btn_sound->setStyleSheet("* { background-color: rgba(0, 0, 0, 0);"
"                                      color: #FFFFFF;"
"                                      font-size: 8px}");
     /****************************** BTN LAUNCHER ******************************/
    ui->btn_login->setStyleSheet("* { background-color: rgba(0, 0, 0, 0);"
"                                     font-size: 10px; }");

    ui->btn_register->setStyleSheet("* { background-color: rgba(0, 0, 0, 0);"
"                                        font-size: 10px; }");

    ui->btn_play->setStyleSheet("* { background-color: rgba(0, 0, 0, 0);"
"                                    font-size: 12px; }");
}

void MainWindow::setFont()
{
    int id = QFontDatabase::addApplicationFont(":/fonts/ethnocentric.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont ethnocentric(family, 8);
    QApplication::setFont(ethnocentric);
}

void MainWindow::setBackground()
{
    QPixmap bkgnd(":/img/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

void MainWindow::playClickSound()
{
    //QSound::play(":/sounds/click.wav");
}

void MainWindow::manageSound(bool mute)
{
    if(mute)
    {
        ui->btn_sound->setIcon(*muteIcon);
    }
    else
    {
        ui->btn_sound->setIcon(*soundIcon);
    }
}

void MainWindow::changeLoginVisibilty()
{
   if(ui->le_username->text() != NULL && ui->le_password->text() != NULL) ui->btn_login->setEnabled(true);
   else ui->btn_login->setEnabled(false);
}

void MainWindow::on_le_id_textEdited()
{
    changeLoginVisibilty();
}

/************************* MOUSE EVENT ****************************************/
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

/************************* BTN ****************************************/
void MainWindow::on_btn_register_clicked()
{
    QDesktopServices::openUrl(QUrl(REGISTER_URL));
    playClickSound();
}

void MainWindow::on_btn_login_clicked()
{
    emit login(ui->le_username->text(), ui->le_password->text());
    emit getPlayerName(ui->le_username->text());
    playClickSound();
}

void MainWindow::on_btn_play_clicked()
{
    emit startGame();
    playClickSound();
}

void MainWindow::on_btn_exit_clicked()
{
    QApplication::exit();
    playClickSound();
}

void MainWindow::on_btn_reduce_clicked()
{
    this->showMinimized();
}

/************************* LINE EDIT ****************************************/
void MainWindow::on_le_username_textEdited()
{
    changeLoginVisibilty();
    playClickSound();
}

void MainWindow::on_le_password_textEdited()
{
    changeLoginVisibilty();
    playClickSound();
}

void MainWindow::on_lineEdit_returnPressed()
{
    emit commandCommit(ui->lineEdit->text());
}

void MainWindow::on_btn_sound_clicked()
{
    emit changeSound();
}
