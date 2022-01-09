QT -= qt core gui

TARGET = KitsunemimiHanamiSdk
CONFIG += c++17
TEMPLATE = lib
VERSION = 0.1.0

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

LIBS += -lssl -lcryptopp

INCLUDEPATH += $$PWD \
               $$PWD/../include

HEADERS += \
    ../include/libKitsunemimiHanamiSdk/actions/cluster.h \
    ../include/libKitsunemimiHanamiSdk/actions/task.h \
    ../include/libKitsunemimiHanamiSdk/actions/template.h \
    ../include/libKitsunemimiHanamiSdk/actions/train_data.h \
    ../include/libKitsunemimiHanamiSdk/actions/user.h \
    ../include/libKitsunemimiHanamiSdk/common/hanami_request.h

SOURCES += \
    actions/cluster.cpp \
    actions/task.cpp \
    actions/template.cpp \
    actions/train_data.cpp \
    actions/user.cpp \
    common/hanami_request.cpp


