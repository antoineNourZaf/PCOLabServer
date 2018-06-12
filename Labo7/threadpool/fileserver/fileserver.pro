QT       += core websockets
QT       -= gui

TARGET = fileserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    fileserver.cpp \
    filereader.cpp \
    requesthandler.cpp \
    responsedispatcherthread.cpp \
    requestdispatcherthread.cpp \
    threadpool.cpp \
    hoaremonitor.cpp \
    runnablelauncher.cpp \
    prodconsbuffer.cpp \
    requesthandlerrunnable.cpp

HEADERS += \
    fileserver.h \
    filereader.h \
    response.h \
    abstractbuffer.h \
    request.h \
    requesthandler.h \
    responsedispatcherthread.h \
    requestdispatcherthread.h \
    prodconsbuffer.h \
    runnable.h \
    threadpool.h \
    hoaremonitor.h \
    runnablelauncher.h \
    requesthandlerrunnable.h

EXAMPLE_FILES += fileclient.html

DISTFILES += \
    shakespeare.txt

