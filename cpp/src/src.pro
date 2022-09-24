QT -= qt core gui

TARGET = KitsumiAiSdk
CONFIG += c++17
TEMPLATE = lib
VERSION = 0.3.1

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
    ../include/libHanamiAiSdk/cluster.h \
    ../include/libHanamiAiSdk/data_set.h \
    ../include/libHanamiAiSdk/init.h \
    ../include/libHanamiAiSdk/project.h \
    ../include/libHanamiAiSdk/request_result.h \
    ../include/libHanamiAiSdk/task.h \
    ../include/libHanamiAiSdk/template.h \
    ../include/libHanamiAiSdk/user.h \
    ../include/libHanamiAiSdk/snapshot.h \
    ../include/libHanamiAiSdk/io.h \
    common/http_client.h \
    ../include/libHanamiAiSdk/common/websocket_client.h \
    ../../../libKitsunemimiHanamiMessages/hanami_messages/kyouko_messages.h \
    ../../../libKitsunemimiHanamiMessages/hanami_messages/sagiri_messages.h

SOURCES += \
    cluster.cpp \
    data_set.cpp \
    init.cpp \
    io.cpp \
    project.cpp \
    request_result.cpp \
    task.cpp \
    template.cpp \
    user.cpp \
    snapshot.cpp \
    common/http_client.cpp \
    common/websocket_client.cpp
