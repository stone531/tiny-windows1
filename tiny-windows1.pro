QT       += core gui sql

#QMAKE_LFLAGS += /MANIFESTUAC:"level='requireAdministrator'uiAccess='false'"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += UNICODE

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DataBase/dbconn.cpp \
    DataBase/mysqlhelper.cpp \
    DataBase/sqlitehelper.cpp \
    addvirusdialog.cpp \
    bridgemanager.cpp \
    buttondelegate.cpp \
    datamanager.cpp \
    main.cpp \
    mainwindow.cpp \
    tablemodel.cpp \
    tableview.cpp \
    virusmanagerwindow.cpp

HEADERS += \
    DataBase/dbconn.h \
    DataBase/dbhelper.h \
    DataBase/mysqlhelper.h \
    DataBase/sqlitehelper.h \
    addvirusdialog.h \
    bridgemanager.h \
    buttondelegate.h \
    common.h \
    datamanager.h \
    mainwindow.h \
    tablemodel.h \
    tableview.h \
    virusmanagerwindow.h

FORMS += \
    addvirusdialog.ui \
    bridgemanager.ui \
    mainwindow.ui \
    virusmanagerwindow.ui

LIBS += -luser32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
