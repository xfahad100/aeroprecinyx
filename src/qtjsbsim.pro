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

INCLUDEPATH += ./ ./example /usr/local/include/JSBSim /usr/include/plib

#-------------------------------------------------

LIBS += -L/usr/lib -lplibjs -lplibul

#-------------------------------------------------

HEADERS += \
    qfi_PFD.h \
    LayoutSquare.h \
    MainWindow.h \
    WidgetPFD.h \
    jsbsim.h

SOURCES += \
    qfi_PFD.cpp \
    LayoutSquare.cpp \
    main.cpp \
    MainWindow.cpp \
    WidgetPFD.cpp \
    jsbsim.cpp

FORMS += \
    MainWindow.ui \
    WidgetPFD.ui

RESOURCES += \
    qtjsbsim.qrc

OTHER_FILES +=
