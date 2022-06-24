#include <libKitsunemimiHanamiSdk/messages/hanami_messages.h>


namespace Kitsunemimi
{
namespace Hanami
{

/**
 * @brief ClusterInput_Message::ClusterInput_Message
 */
ClusterIO_Message::ClusterIO_Message()
{
    m_type = 1;
}

/**
 * @brief ClusterInput_Message::~ClusterInput_Message
 */
ClusterIO_Message::~ClusterIO_Message() {}

/**
 * @brief ClusterInput_Message::read
 * @param data
 * @param dataSize
 * @return
 */
bool
ClusterIO_Message::read(void* data, const uint64_t dataSize)
{
    if(initRead(data, dataSize) == false) {
        return false;
    }

    if(readUint(data, segmentType) == false) {
        return false;
    }
    if(readUint(data, segmentId) == false) {
        return false;
    }
    if(readFloatList(data, &values, numberOfValues) == false) {
        return false;
    }

    return true;
}

/**
 * @brief ClusterInput_Message::createBlob
 * @param result
 */
void
ClusterIO_Message::createBlob(DataBuffer &result)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader)
                                  + 3 * sizeof(Entry)
                                  + 2 * sizeof(uint64_t)
                                  + numberOfValues * sizeof(float);

    initBlob(result, totalMsgSize);
    appendUint(result, segmentType);
    appendUint(result, segmentId);
    appendFloatList(result, values, numberOfValues);
}

/**
 * @brief RequestStart_Message::RequestStart_Message
 */
RequestStart_Message::RequestStart_Message()
{
    m_type = 2;
}

/**
 * @brief RequestStart_Message::~RequestStart_Message
 */
RequestStart_Message::~RequestStart_Message() {}

/**
 * @brief RequestStart_Message::read
 * @param data
 * @param dataSize
 * @return
 */
bool
RequestStart_Message::read(void* data, const uint64_t dataSize)
{
    if(initRead(data, dataSize) == false) {
        return false;
    }

    return true;
}

/**
 * @brief RequestStart_Message::createBlob
 * @param result
 */
void
RequestStart_Message::createBlob(DataBuffer &result)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader);
    initBlob(result, totalMsgSize);
}

/**
 * @brief LearnStart_Message::LearnStart_Message
 */
LearnStart_Message::LearnStart_Message()
{
    m_type = 3;
}

/**
 * @brief LearnStart_Message::~LearnStart_Message
 */
LearnStart_Message::~LearnStart_Message() {}

/**
 * @brief LearnStart_Message::read
 * @param data
 * @param dataSize
 * @return
 */
bool
LearnStart_Message::read(void* data, const uint64_t dataSize)
{
    if(initRead(data, dataSize) == false) {
        return false;
    }

    return true;
}

/**
 * @brief LearnStart_Message::createBlob
 * @param result
 */
void
LearnStart_Message::createBlob(DataBuffer &result)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader);
    initBlob(result, totalMsgSize);
}

/**
 * @brief RequestEnd_Message::RequestEnd_Message
 */
RequestEnd_Message::RequestEnd_Message()
{
    m_type = 4;
}

/**
 * @brief RequestEnd_Message::~RequestEnd_Message
 */
RequestEnd_Message::~RequestEnd_Message() {}

/**
 * @brief RequestEnd_Message::read
 * @param data
 * @param dataSize
 * @return
 */
bool
RequestEnd_Message::read(void *data, const uint64_t dataSize)
{
    if(initRead(data, dataSize) == false) {
        return false;
    }

    return true;
}

/**
 * @brief RequestEnd_Message::createBlob
 * @param result
 */
void
RequestEnd_Message::createBlob(DataBuffer &result)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader);
    initBlob(result, totalMsgSize);
}

/**
 * @brief LearnEnd_Message::LearnEnd_Message
 */
LearnEnd_Message::LearnEnd_Message()
{
    m_type = 5;
}

/**
 * @brief LearnEnd_Message::~LearnEnd_Message
 */
LearnEnd_Message::~LearnEnd_Message() {}

/**
 * @brief LearnEnd_Message::read
 * @param data
 * @param dataSize
 * @return
 */
bool
LearnEnd_Message::read(void *data, const uint64_t dataSize)
{
    if(initRead(data, dataSize) == false) {
        return false;
    }

    return true;
}

/**
 * @brief LearnEnd_Message::createBlob
 * @param result
 */
void
LearnEnd_Message::createBlob(DataBuffer &result)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader);
    initBlob(result, totalMsgSize);
}

}  // namespace Hanami
}  // namespace Kitsunemimi
