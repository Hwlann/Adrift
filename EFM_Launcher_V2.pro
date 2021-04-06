QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Command/admincommand.cpp \
    Command/command.cpp \
    Command/forceexitcommand.cpp \
    Command/logcommand.cpp \
    Core/launchermanager.cpp \
    Core/main.cpp \
    Launcher/music.cpp \
    Logger/logger.cpp \
    Launcher/mainwindow.cpp \
    Network/networkmanager.cpp \
    Command/forcepath.cpp

HEADERS += \
    Command/admincommand.h \
    Command/command.h \
    Command/forceexitcommand.h \
    Command/forcepath.h \
    Command/logcommand.h \
    Core/launchermanager.h \
    Launcher/music.h \
    Logger/logger.h \
    Launcher/mainwindow.h \
    Network/networkmanager.h \
    Command/forcepath.h

FORMS += \
    Logger/logger.ui \
    Launcher/mainwindow.ui

RESOURCES += \
    res.qrc

RC_ICONS = logo.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
