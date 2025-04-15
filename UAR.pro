QT       += core gui charts widgets network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ARX.cpp \
    Generator.cpp \
    PID.cpp \
    Symulator.cpp \
    TCPserwer.cpp \
    ZarzadzanieSiec.cpp \
    arx_window.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ARX.h \
    Generator.h \
    PID.h \
    Symulator.h \
    TCPserwer.h \
    ZarzadzanieSiec.h \
    arx_window.h \
    mainwindow.h

FORMS += \
    PobieranieAdresuIportu.ui \
    arx_window.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
