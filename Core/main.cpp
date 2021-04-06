#include "Core/launchermanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LauncherManager::getInstance();
    return a.exec();
}
