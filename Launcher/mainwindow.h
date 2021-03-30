#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <QMouseEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define     WINDOW_WIDTH    450
#define     WINDOW_HEIGHT   620
#define     WINDOW_TITLE    "EFM Launcher"

#define     REGISTER_URL    ""

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

private slots:
    void on_lineEdit_returnPressed();
    void on_btn_register_clicked();
    void on_pushButton_clicked();
    void changeLoginVisibilty();
    void on_le_id_textEdited();
    void on_le_password_textEdited();
    void on_btn_startGame_clicked();

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
