QT += core
QT -= gui

CONFIG += c++11

TARGET = Labo2
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    mythread.h \
    utils.h
