#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <QMouseEvent>
#include <QPainter>
#include <QFontDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define     WINDOW_WIDTH    350
#define     WINDOW_HEIGHT   550
#define     WINDOW_TITLE    "EFM Launcher"

#define     REGISTER_URL    "http://lortetcesar.fr/"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Instance & Destructor
    static MainWindow *getInstance(QWidget *parent = nullptr);
    ~MainWindow();

    // UI
    void setupUi();
    void changeStatusbarText(QString *text);
    void changeStartGameBtn(bool enable);
    void setStyleSheets();
    void setFont();
    void setBackground();

private slots:
    void on_lineEdit_returnPressed();
    void changeLoginVisibilty();
    void on_le_id_textEdited();
    void on_btn_register_clicked();
    void on_btn_login_clicked();
    void on_btn_play_clicked();
    void on_le_username_textEdited();
    void on_le_password_textEdited();
    void on_btn_exit_clicked();
    void on_btn_reduce_clicked();

protected:
        void mousePressEvent(QMouseEvent *evt);
        void mouseMoveEvent(QMouseEvent *evt);


private:
    static MainWindow *m_mainWindow;
    MainWindow(QWidget *parent = nullptr);
    Ui::MainWindow *ui;
    QPoint oldPos;
    bool locked = false;

signals:
    void commandCommit(QString cmd);
    void login(QString id, QString password);
    void getPlayerName(QString id);
    void startGame();

};
#endif // MAINWINDOW_H
