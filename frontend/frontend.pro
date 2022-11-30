QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bankwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    nostosummawindow.cpp \
    nostowindow.cpp \
    saldowindow.cpp \
    tapahtumawindow.cpp \
    url.cpp

HEADERS += \
    bankwindow.h \
    mainwindow.h \
    nostosummawindow.h \
    nostowindow.h \
    saldowindow.h \
    tapahtumawindow.h \
    url.h

FORMS += \
    bankwindow.ui \
    mainwindow.ui \
    nostosummawindow.ui \
    nostowindow.ui \
    saldowindow.ui \
    tapahtumawindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
