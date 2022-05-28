QT -= qt core gui

TARGET = KitsunemimiHanamiSdk
CONFIG += c++17
TEMPLATE = lib
VERSION = 0.2.0

LIBS += -L../../libKitsunemimiCommon/src -lKitsunemimiCommon
LIBS += -L../../libKitsunemimiCommon/src/debug -lKitsunemimiCommon
LIBS += -L../../libKitsunemimiCommon/src/release -lKitsunemimiCommon
INCLUDEPATH += ../../../libKitsunemimiCommon/include

LIBS += -L../../libKitsunemimiJson/src -lKitsunemimiJson
LIBS += -L../../libKitsunemimiJson/src/debug -lKitsunemimiJson
LIBS += -L../../libKitsunemimiJson/src/release -lKitsunemimiJson
INCLUDEPATH += ../../../libKitsunemimiJson/include

LIBS += -L../../libKitsunemimiCrypto/src -lKitsunemimiCrypto
LIBS += -L../../libKitsunemimiCrypto/src/debug -lKitsunemimiCrypto
LIBS += -L../../libKitsunemimiCrypto/src/release -lKitsunemimiCrypto
INCLUDEPATH += ../../../libKitsunemimiCrypto/include

LIBS += -L../../libKitsunemimiHanamiCommon/src -lKitsunemimiHanamiCommon
LIBS += -L../../libKitsunemimiHanamiCommon/src/debug -lKitsunemimiHanamiCommon
LIBS += -L../../libKitsunemimiHanamiCommon/src/release -lKitsunemimiHanamiCommon
INCLUDEPATH += ../../../libKitsunemimiHanamiCommon/include

LIBS += -lssl -lcryptopp -lcrypt

INCLUDEPATH += $$PWD \
               $$PWD/../include

HEADERS += \
    ../include/libKitsunemimiHanamiSdk/actions/cluster.h \
    ../include/libKitsunemimiHanamiSdk/actions/data_set.h \
    ../include/libKitsunemimiHanamiSdk/actions/task.h \
    ../include/libKitsunemimiHanamiSdk/actions/template.h \
    ../include/libKitsunemimiHanamiSdk/actions/user.h \
    ../include/libKitsunemimiHanamiSdk/actions/snapshot.h \
    ../include/libKitsunemimiHanamiSdk/common/http_client.h \
    common/websocket_client.h

SOURCES += \
    actions/cluster.cpp \
    actions/data_set.cpp \
    actions/task.cpp \
    actions/template.cpp \
    actions/user.cpp \
    actions/snapshot.cpp \
    common/http_client.cpp \
    common/websocket_client.cpp


