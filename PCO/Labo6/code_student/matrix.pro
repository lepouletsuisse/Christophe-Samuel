TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += debug
CONFIG += c++11

SOURCES += src/main.cpp \
    src/hoaremonitor.cpp

INCLUDEPATH += src

HEADERS += \
    src/matrix.h \
    src/abstractmatrixmultiplier.h \
    src/simplematrixmultiplier.h \
    src/threadedmatrixmultiplier.h \
    src/multipliertester.h \
    src/multiplierthreadedtester.h \
    src/hoaremonitor.h \
    src/squarematrixwrapper.h \
    src/worker.h \
    src/workermanager.h

