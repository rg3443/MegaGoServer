QT       += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    main.cpp \
    mainwindow.cpp \
    mgserver.cpp

HEADERS += \
    client.h \
    mainwindow.h \
    mgserver.h

FORMS += \
    mainwindow.ui


############################################################################################################

#### MysqlConnector lib ####
DEPENDPATH += C:\wrk\proj\MegaGoModel
INCLUDEPATH += C:\wrk\proj\MegaGoModel
LIBS += -LC:\wrk\proj\build-MegaGoModel-Desktop_Qt_5_12_12_MinGW_64_bit-Debug\debug -lMegaGoModel

############################################################################################################

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
