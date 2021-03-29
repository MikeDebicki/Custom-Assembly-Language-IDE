#-------------------------------------------------
#
# Project created by QtCreator 2019-11-06T20:06:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scapesUI
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

CONFIG += c++11

SOURCES += \
        addstmt.cpp \
        compilecontrol.cpp \
        compstmt.cpp \
        declarrstmt.cpp \
        declintstmt.cpp \
        endstmt.cpp \
        errorcheck.cpp \
        identifier.cpp \
        jeqstmt.cpp \
        jlessstmt.cpp \
        jmorestmt.cpp \
        jumpstmt.cpp \
        label.cpp \
        main.cpp \
        mainwindow.cpp \
        movstmt.cpp \
        operand.cpp \
        printstmt.cpp \
        program.cpp \
        readstmt.cpp \
        runcontrol.cpp \
        statement.cpp \
        statementfactory.cpp \
        variable.cpp

HEADERS += \
    addstmt.h \
    compilecontrol.h \
    compstmt.h \
    declarrstmt.h \
    declintstmt.h \
    endstmt.h \
    errorcheck.h \
    identifier.h \
    jeqstmt.h \
    jlessstmt.h \
    jmorestmt.h \
    jumpstmt.h \
    label.h \
    mainwindow.h \
    movstmt.h \
    operand.h \
    printstmt.h \
    program.h \
    readstmt.h \
    runcontrol.h \
    statement.h \
    statementfactory.h \
    variable.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
