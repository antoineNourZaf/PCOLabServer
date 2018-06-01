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
    requesthandlerthread.cpp \
    threadpool.cpp \
    hoaremonitor.cpp

HEADERS += \
    fileserver.h \
    filereader.h \
    response.h \
    abstractbuffer.h \
    request.h \
    requesthandler.h \
    responsedispatcherthread.h \
    requestdispatcherthread.h \
    requesthandlerthread.h \
    prodconsbuffer.h \
    prodconsbuffer.hpp \
    runnable.h \
    threadpool.h \
    hoaremonitor.h

EXAMPLE_FILES += fileclient.html

DISTFILES += \
    shakespeare.txt

