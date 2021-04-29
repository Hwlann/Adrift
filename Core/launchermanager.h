#ifndef LAUNCHERMANAGER_H
#define LAUNCHERMANAGER_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QSoundEffect>
#include <QSound>
#include <QThread>
#include <QDir>
#include <QCursor>

#include "Launcher/mainwindow.h"
#include "Network/networkmanager.h"

#include "Command/admincommand.h"
#include "Command/forceexitcommand.h"
#include "Command/logcommand.h"
#include "Command/forcepath.h"

#define  CMD_SHOW_LOGS "show logs"
#define  ADMIN_TOKEN   "46e9e734-915e-11eb-8c90-0242ac110007"

#define  GAME_PATH     "bin/EscapeFromMorkov.exe"
#define  MUSIC_PATH    ":/sounds/res/sounds/N3WPORT_Meggie-York-Runaway_NCS-Release.wav"


#define     HOVER_SOUND     ":/sounds/res/sounds/hover.wav"
#define     CLICK_SOUND     ":/sounds/res/sounds/selected.wav"


class LauncherManager : public QObject
{
    Q_OBJECT
public:
    static LauncherManager *getInstance();
    ~LauncherManager();

    void startGame();
    void defineGamesOptions();    
    void setSounds();

public slots:
    void musicManager(bool force = false, bool mute = false);    
    void playClickSound();
    void playHoverSound();

private:
    explicit LauncherManager(QObject *parent = nullptr);
    static LauncherManager *m_launcherManager;

    MainWindow *m_mainWindow = nullptr;
    QProcess *m_gameProcess = nullptr;
    NetworkManager *m_networkManager = nullptr;
    Logger *m_logger = nullptr;

    QString m_programPath = "bin/EscapeFromMorkov.exe";
    QStringList m_programArgs;
    void changeWindowsVisibility(bool visibility);

    bool m_startAsAdmin = false;
    bool m_isAdmin = false;

    QString m_playerName = NULL;
    QString m_userAccessToken = NULL;

    QString m_musicPath = MUSIC_PATH;
    QSoundEffect *m_music;
    bool m_mute = false;

signals:

private slots:
    void parseCommand(QString cmd);
    void gameStateChanged();
    void gameError();
    void executeCommand(Command::COMMAND cmd, QString command);
    void loginCheck(QString token);
    void setupPlayer(QString id);    
    void processDownloadedFile(QFile *file);
};

#endif // LAUNCHERMANAGER_H
