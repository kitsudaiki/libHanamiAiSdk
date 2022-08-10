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

LIBS += -lssl -lcryptopp -lcrypt -pthread -lprotobuf -lpthread

INCLUDEPATH += $$PWD \
               $$PWD/../include

HEADERS += \
    ../include/libKitsumiAiSdk/cluster.h \
    ../include/libKitsumiAiSdk/data_set.h \
    ../include/libKitsumiAiSdk/init.h \
    ../include/libKitsumiAiSdk/task.h \
    ../include/libKitsumiAiSdk/template.h \
    ../include/libKitsumiAiSdk/user.h \
    ../include/libKitsumiAiSdk/snapshot.h \
    ../include/libKitsumiAiSdk/io.h \
    common/http_client.h \
    ../include/libKitsumiAiSdk/common/websocket_client.h

SOURCES += \
    cluster.cpp \
    data_set.cpp \
    init.cpp \
    io.cpp \
    task.cpp \
    template.cpp \
    user.cpp \
    snapshot.cpp \
    common/http_client.cpp \
    common/websocket_client.cpp

SAGIRI_PROTO_BUFFER = ../../../libKitsunemimiHanamiProtobuffers/sagiri_messages.proto3
KYOUKO_PROTO_BUFFER = ../../../libKitsunemimiHanamiProtobuffers/kyouko_messages.proto3

OTHER_FILES += $$KYOUKO_PROTO_BUFFER \
               $$SAGIRI_PROTO_BUFFER

protobuf_sagiri_decl.name = protobuf sagiri headers
protobuf_sagiri_decl.input = SAGIRI_PROTO_BUFFER
protobuf_sagiri_decl.output = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.proto3.pb.h
protobuf_sagiri_decl.commands = protoc --cpp_out=${QMAKE_FILE_IN_PATH} --proto_path=${QMAKE_FILE_IN_PATH} ${QMAKE_FILE_NAME}
protobuf_sagiri_decl.variable_out = HEADERS
QMAKE_EXTRA_COMPILERS += protobuf_sagiri_decl

protobuf_sagiri_impl.name = protobuf sagiri sources
protobuf_sagiri_impl.input = SAGIRI_PROTO_BUFFER
protobuf_sagiri_impl.output = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.proto3.pb.cc
protobuf_sagiri_impl.depends = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.proto3.pb.h
protobuf_sagiri_impl.commands = $$escape_expand(\n)
protobuf_sagiri_impl.variable_out = SOURCES
QMAKE_EXTRA_COMPILERS += protobuf_sagiri_impl

protobuf_kyouko_decl.name = protobuf kyouko headers
protobuf_kyouko_decl.input = KYOUKO_PROTO_BUFFER
protobuf_kyouko_decl.output = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.proto3.pb.h
protobuf_kyouko_decl.commands = protoc --cpp_out=${QMAKE_FILE_IN_PATH} --proto_path=${QMAKE_FILE_IN_PATH} ${QMAKE_FILE_NAME}
protobuf_kyouko_decl.variable_out = HEADERS
QMAKE_EXTRA_COMPILERS += protobuf_kyouko_decl

protobuf_kyouko_impl.name = protobuf kyouko sources
protobuf_kyouko_impl.input = KYOUKO_PROTO_BUFFER
protobuf_kyouko_impl.output = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.proto3.pb.cc
protobuf_kyouko_impl.depends = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.proto3.pb.h
protobuf_kyouko_impl.commands = $$escape_expand(\n)
protobuf_kyouko_impl.variable_out = SOURCES
QMAKE_EXTRA_COMPILERS += protobuf_kyouko_impl



