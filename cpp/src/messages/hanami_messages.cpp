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

}  // namespace Hanami
}  // namespace Kitsunemimi
