QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    App/main.cpp \
    Common/EnemyPath.cpp \
    Common/Music.cpp \
    Common/plistreader.cpp \
    Common/utility.cpp \
    Model/Bullet.cpp \
    Model/Enemy.cpp \
    Model/Game.cpp \
    Model/Tower.cpp \
    View/mainwindow.cpp \
    Viewmodel/Button.cpp \
    Viewmodel/LevelSelect.cpp

HEADERS += \
    Common/EnemyPath.h \
    Common/Music.h \
    Common/plistreader.h \
    Common/utility.h \
    Model/Bullet.h \
    Model/Enemy.h \
    Model/Game.h \
    Model/Tower.h \
    View/mainwindow.h \
    Viewmodel/Button.h \
    Viewmodel/LevelSelect.h

FORMS += \
    View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    Resource/music/EnemyDestorySound1.mp3 \
    Resource/music/EnemyDestorySound2.mp3 \
    Resource/music/EnemyDestorySound3.mp3 \
    Resource/music/EnemyDestorySound4.mp3 \
    Resource/music/EnemyDestroySound1.mp3 \
    Resource/music/EnemyDestroySound2.mp3 \
    Resource/music/EnemyDestroySound3.mp3 \
    Resource/music/EnemyDestroySound4.mp3 \
    Resource/music/First Page.mp3 \
    Resource/music/Lose.mp3 \
    Resource/music/Win.mp3 \
    Resource/music/bgmusic2.mp3 \
    Resource/music/bossEnemyDie.mp3 \
    Resource/music/easy.mp3 \
    Resource/music/fastEnemyDie.mp3 \
    Resource/music/fireBullet.mp3 \
    Resource/music/fireEnemyDie.mp3 \
    Resource/music/hard.mp3 \
    Resource/music/iceBullet.mp3 \
    Resource/music/iceEnemyDie.mp3 \
    Resource/music/laserBullet.mp3 \
    Resource/music/levelmusic.mp3 \
    Resource/music/life_lose.mp3 \
    Resource/music/mainmusic.mp3 \
    Resource/music/normalBullet.mp3 \
    Resource/music/normalEnemyDie.mp3 \
    Resource/music/tower_place.mp3
