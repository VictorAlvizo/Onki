#-------------------------------------------------
#
# Project created by QtCreator 2018-12-09T15:35:35
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Onki
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 resources_big

SOURCES += \
        main.cpp \
    game.cpp \
    button.cpp \
    slider.cpp \
    player.cpp \
    healthbar.cpp \
    enemy.cpp \
    goblin.cpp \
    witch.cpp \
    tree.cpp \
    projectile.cpp \
    witchprojectile.cpp \
    border.cpp \
    pond.cpp \
    weapon.cpp \
    playerprojectile.cpp \
    m1911.cpp \
    pickupitem.cpp \
    m1911pickup.cpp \
    m16.cpp \
    m16pickup.cpp \
    healthpotionpickup.cpp \
    yspickup.cpp \
    pickuptext.cpp \
    githubbutton.cpp \
    rampet.cpp \
    lotus.cpp \
    lotusprojectile.cpp \
    mp5.cpp \
    mp5pickup.cpp \
    cobra.cpp \
    cobrapickup.cpp \
    healthpack.cpp \
    wsshirtpickup.cpp \
    lstmusicpickup.cpp \
    fvpickup.cpp \
    trademarkanim.cpp

HEADERS += \
    game.h \
    button.h \
    slider.h \
    player.h \
    healthbar.h \
    enemy.h \
    goblin.h \
    witch.h \
    tree.h \
    projectile.h \
    witchprojectile.h \
    border.h \
    pond.h \
    weapon.h \
    playerprojectile.h \
    m1911.h \
    pickupitem.h \
    m1911pickup.h \
    m16.h \
    m16pickup.h \
    healthpotionpickup.h \
    yspickup.h \
    pickuptext.h \
    githubbutton.h \
    rampet.h \
    lotus.h \
    lotusprojectile.h \
    mp5.h \
    mp5pickup.h \
    cobra.h \
    cobrapickup.h \
    healthpack.h \
    wsshirtpickup.h \
    lstmusicpickup.h \
    fvpickup.h \
    trademarkanim.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
