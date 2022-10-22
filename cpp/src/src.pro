QT -= qt core gui

TARGET = HanamiAiSdk
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
    ../include/libHanamiAiSdk/common/websocket_client.h

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


SHIORI_PROTO_BUFFER = ../../../libKitsunemimiHanamiMessages/protobuffers/shiori_messages.proto3
KYOUKO_PROTO_BUFFER = ../../../libKitsunemimiHanamiMessages/protobuffers/kyouko_messages.proto3

OTHER_FILES += $$KYOUKO_PROTO_BUFFER
OTHER_FILES += $$SHIORI_PROTO_BUFFER

protobuf_decl_shiori.name = protobuf headers
protobuf_decl_shiori.input = SHIORI_PROTO_BUFFER
protobuf_decl_shiori.output = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.proto3.pb.h
protobuf_decl_shiori.commands = protoc --cpp_out=${QMAKE_FILE_IN_PATH} --proto_path=${QMAKE_FILE_IN_PATH} ${QMAKE_FILE_NAME}
protobuf_decl_shiori.variable_out = HEADERS
QMAKE_EXTRA_COMPILERS += protobuf_decl_shiori

protobuf_impl_shiori.name = protobuf sources
protobuf_impl_shiori.input = SHIORI_PROTO_BUFFER
protobuf_impl_shiori.output = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.proto3.pb.cc
protobuf_impl_shiori.depends = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.proto3.pb.h
protobuf_impl_shiori.commands = $$escape_expand(\n)
protobuf_impl_shiori.variable_out = SOURCES
QMAKE_EXTRA_COMPILERS += protobuf_impl_shiori


protobuf_decl_kyouko.name = protobuf headers
protobuf_decl_kyouko.name = protobuf headers
protobuf_decl_kyouko.input = KYOUKO_PROTO_BUFFER
protobuf_decl_kyouko.output = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.proto3.pb.h
protobuf_decl_kyouko.commands = protoc --cpp_out=${QMAKE_FILE_IN_PATH} --proto_path=${QMAKE_FILE_IN_PATH} ${QMAKE_FILE_NAME}
protobuf_decl_kyouko.variable_out = HEADERS
QMAKE_EXTRA_COMPILERS += protobuf_decl_kyouko

protobuf_impl_kyouko.name = protobuf sources
protobuf_impl_kyouko.input = KYOUKO_PROTO_BUFFER
protobuf_impl_kyouko.output = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.proto3.pb.cc
protobuf_impl_kyouko.depends = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.proto3.pb.h
protobuf_impl_kyouko.commands = $$escape_expand(\n)
protobuf_impl_kyouko.variable_out = SOURCES
QMAKE_EXTRA_COMPILERS += protobuf_impl_kyouko
