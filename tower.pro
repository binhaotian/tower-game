QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 debug

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Base.cpp\
    Map.cpp\
    Scene.cpp\
    Bar.cpp\
    Bullet.cpp\
    Entity.cpp\
    Follower.cpp\
    HealthBar.cpp\
    Unit.cpp\
    Enemy.cpp\
    Tower.cpp\
    GameView.cpp\
    main.cpp

HEADERS += \
    Base.h\
    Map.h\
    Scene.h\
    Bar.h\
    Bullet.h\
    Entity.h\
    Follower.h\
    HealthBar.h\
    Unit.h\
    Enemy.h\
    Tower.h\
    GameView.h

RESOURCES += resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
