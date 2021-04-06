#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <QMouseEvent>
#include <QPainter>
#include <QFontDatabase>
#include <QSoundEffect>
#include <QSound>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define     WINDOW_WIDTH    350
#define     WINDOW_HEIGHT   550
#define     WINDOW_TITLE    "EFM Launcher"

#define     REGISTER_URL    "http://lortetcesar.fr/"
#define     DEF_VOLUME      0.25f

// Click sound : https://freesound.org/s/399934/
// Music : Portal Sound Track, Portal Soundtrack - Self Esteem Fund ,https://www.youtube.com/watch?v=t9nocjg2OLI

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
    void setSounds();
    void playClickSound();
    void manageSound(bool force = false, bool mute = false);    
    void clearLineEditCommand();

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
    void on_btn_sound_clicked();

protected:
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);


private:
    static MainWindow *m_mainWindow;
    MainWindow(QWidget *parent = nullptr);
    Ui::MainWindow *ui;
    QPoint oldPos;
    bool locked = false;
    QString m_musicPath = ":/sounds/Portal-SelfEsteemFund.wav";
    QSoundEffect *m_music;
    bool m_volume = true;

    QPixmap *m_soundOnPixmap;
    QPixmap *m_mutePixmap;

    QIcon *soundIcon;
    QIcon *muteIcon;

signals:
    void commandCommit(QString cmd);
    void login(QString id, QString password);
    void getPlayerName(QString id);
    void startGame();

};
#endif // MAINWINDOW_H
