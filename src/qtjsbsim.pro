#-------------------------------------------------
#
# Project created by QtCreator 2013-09-24T17:03:18
#
#-------------------------------------------------

QT       += core gui svg network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtjsbsim
TEMPLATE = app

#-------------------------------------------------

win32: DEFINES += WIN32 _WINDOWS _USE_MATH_DEFINES

win32:CONFIG(release, debug|release):    DEFINES += NDEBUG
else:win32:CONFIG(debug, debug|release): DEFINES += _DEBUG

#-------------------------------------------------

INCLUDEPATH += ./ ./QFI ./autopilot /usr/local/include/JSBSim /usr/include/plib

#-------------------------------------------------

LIBS += -L/usr/lib -lplibjs -lplibul

#-------------------------------------------------

HEADERS += \
    MainWindow.h \
    WidgetPFD.h \
    jsbsim.h \
    QFI/LayoutSquare.h \
    QFI/qfi_ADI.h \
    QFI/qfi_PFD.h \
    QFI/WidgetPFD.h \
    autopilot/PID_v1.h

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    jsbsim.cpp \
    QFI/LayoutSquare.cpp \
    QFI/qfi_PFD.cpp \
    QFI/WidgetPFD.cpp \
    autopilot/PID_v1.cpp

FORMS += \
    MainWindow.ui \
    QFI/WidgetPFD.ui

RESOURCES += \
    qtjsbsim.qrc

OTHER_FILES +=
