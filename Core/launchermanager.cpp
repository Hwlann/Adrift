#include "launchermanager.h"

LauncherManager *LauncherManager::m_launcherManager = nullptr;

LauncherManager *LauncherManager::getInstance()
{
    if(m_launcherManager == nullptr){
        m_launcherManager = new LauncherManager();
    }
    return m_launcherManager;
}

LauncherManager::~LauncherManager()
{
    delete m_mainWindow;
    delete m_gameProcess;
    delete m_logger;
    delete m_networkManager;
}

void LauncherManager::startGame()
{
    m_programPath = GAME_PATH;

    m_gameProcess = new QProcess();

    connect(m_gameProcess, &QProcess::stateChanged, this, &LauncherManager::gameStateChanged);
    connect(m_gameProcess, &QProcess::errorOccurred, this, &LauncherManager::gameError);

    defineGamesOptions();

    qDebug() << m_programPath;
    qDebug() << "Args : " ;
    qDebug() << m_programArgs;

    musicManager();
    m_gameProcess->setNativeArguments("-token="+m_userAccessToken);
    m_gameProcess->start(m_programPath);

    changeWindowsVisibility(false);
}

void LauncherManager::defineGamesOptions()
{
    if(m_userAccessToken != NULL) m_programArgs << "-token" << m_userAccessToken;
}

LauncherManager::LauncherManager(QObject *parent) : QObject(parent)
{
    m_mainWindow = MainWindow::getInstance(nullptr);
    m_networkManager = NetworkManager::getInstance();
    m_logger = Logger::getInstance();

    connect(m_mainWindow, &MainWindow::login, m_networkManager, &NetworkManager::postCredentials);
    connect(m_mainWindow, &MainWindow::getPlayerName, this, &LauncherManager::setupPlayer);
    connect(m_mainWindow, &MainWindow::commandCommit, this, &LauncherManager::parseCommand);
    connect(m_mainWindow, &MainWindow::startGame, this, &LauncherManager::startGame);
    connect(m_mainWindow, &MainWindow::changeSound, this, &LauncherManager::musicManager);
    connect(m_mainWindow, &MainWindow::playClick, this, &LauncherManager::playClickSound);
    connect(m_mainWindow, &MainWindow::playHover, this, &LauncherManager::playHoverSound);
    connect(m_networkManager, &NetworkManager::loginQueryAnswer, this, &LauncherManager::loginCheck);

    setSounds();
    QPixmap cursorPixmap = QPixmap(":/img/res/images/cursor.png");
    cursorPixmap = cursorPixmap.scaled(20, 20 , Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::FastTransformation);
    QCursor cursor = QCursor(cursorPixmap, 0, 0);
    QApplication::setOverrideCursor(cursor);
}

void LauncherManager::changeWindowsVisibility(bool visibility)
{
    m_mainWindow->setVisible(visibility);
    m_logger->setVisible(visibility);
}

void LauncherManager::parseCommand(QString cmd)
{
    AdminCommand *admin = new AdminCommand();
    ForceExitCommand *fExit = new ForceExitCommand();
    LogCommand *log = new LogCommand();
    ForcePath *path = new ForcePath();

    connect(path, &ForcePath::executeCommand, this, &LauncherManager::executeCommand);
    connect(admin, &AdminCommand::executeCommand, this, &LauncherManager::executeCommand);
    connect(fExit, &ForceExitCommand::executeCommand, this, &LauncherManager::executeCommand);
    connect(log, &LogCommand::executeCommand, this, &LauncherManager::executeCommand);

    path->setNext(admin);
    admin->setNext(fExit);
    fExit->setNext(log);

    path->message(cmd);
}

void LauncherManager::gameStateChanged()
{
    switch(m_gameProcess->state())
    {
        case QProcess::Running:
        break;

        case QProcess::NotRunning:
                musicManager(true, false);
                QApplication::quit();
        break;

        default:
        break;

    }
}

void LauncherManager::gameError()
{

}

void LauncherManager::executeCommand(Command::COMMAND cmd, QString command)
{
    switch(cmd)
    {
        case Command::ADMIN:
        {
            QMessageBox *msgBox = new QMessageBox();
            if(m_userAccessToken == ADMIN_TOKEN)
            {
                m_isAdmin = true;
                m_startAsAdmin = true;
                msgBox->setText("Hi Boss.");

            }
            else
            {
                m_startAsAdmin = false;
                m_isAdmin = false;
                msgBox->setText("Nice Try ..!");

            }
            msgBox->exec();
        }
        break;

        case Command::PATH:
        {
            m_programPath = command;
        }

        case Command::SHOW_LOGS:
        {
            if(command == CMD_SHOW_LOGS)
            {
                Logger::getInstance()->setWindowState(Qt::WindowState::WindowActive);
                Logger::getInstance()->setFocus();
                Logger::getInstance()->activateWindow();
                Logger::getInstance()->show();
            }
            else Logger::getInstance()->hide();
        }

            default:
            break;

    }
    m_mainWindow->clearLineEditCommand();
}

void LauncherManager::loginCheck(QString token)
{
    if(token != NULL)
    {
        m_userAccessToken = token;
        m_mainWindow->changeStartGameBtn(true);
        m_mainWindow->disableLineEdit();
    }
    else
    {
        Logger::getInstance()->addLog(Logger::LogLevel::ERROR, "Wrong username or password");
        QMessageBox msgBox;
        msgBox.setText("Wrong username or password");
        msgBox.exec();
    }
}

void LauncherManager::setupPlayer(QString id)
{
    m_playerName = id;
}

void LauncherManager::processDownloadedFile(QFile *file)
{
    if (!file->fileName().isEmpty()) {
        // Read the file and transform the output to a QByteArray
        /*
        QByteArray ba_files = file->readAll();
        qUncompress(ba_files);
        QDir dir("./bin");
        */
    }
    QFile zipFile("test.zip");

}

void LauncherManager::musicManager(bool force, bool mute)
{
    if(force) m_mute = mute;
    else m_mute = !m_mute;
    m_music->setMuted(!m_mute);
    m_mainWindow->manageSound(m_mute);
}

void LauncherManager::setSounds()
{
    m_music = new QSoundEffect();
    m_music->setSource(QUrl::fromLocalFile(m_musicPath));
    m_music->setLoopCount(QSoundEffect::Infinite);
    m_music->setVolume(DEF_VOLUME);
    m_music->setMuted(m_mute);
    m_music->play();

    musicManager();
}

void LauncherManager::playHoverSound()
{
    QSoundEffect m_hover;
    m_hover.setSource(QUrl::fromLocalFile(CLICK_SOUND));
    m_hover.setVolume(DEF_VOLUME+0.07f);
    m_hover.play();
    qDebug() << __PRETTY_FUNCTION__;
}

void LauncherManager::playClickSound()
{
    QSoundEffect *m_click = new QSoundEffect();
    m_click->setSource(QUrl::fromLocalFile(CLICK_SOUND));
    m_click->setVolume(DEF_VOLUME+0.7f);
    m_click->play();
}
