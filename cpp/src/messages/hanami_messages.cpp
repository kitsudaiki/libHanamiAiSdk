/**
 * @file        hanami_messages.cpp
 *
 * @author      Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 * @copyright   Apache License Version 2.0
 *
 *      Copyright 2021 Tobias Anker
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *          http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#include <libKitsunemimiHanamiSdk/messages/hanami_messages.h>

namespace Kitsunemimi
{
namespace Hanami
{

//==================================================================================================

/**
 * @brief constructor
 */
ClusterIO_Message::ClusterIO_Message()
{
    m_type = 1;
}

/**
 * @brief destructor
 */
ClusterIO_Message::~ClusterIO_Message() {}

/**
 * @brief read message from byte-array
 *
 * @param data pointer to byte-buffer
 * @param dataSize number of bytes
 *
 * @return true, if message was valid, else false
 */
bool
ClusterIO_Message::read(void* data, const uint64_t dataSize)
{
    if(initRead(data, dataSize) == false) {
        return false;
    }

    if(readString(data, segmentName) == false) {
        return false;
    }
    if(readUint(data, segmentType) == false) {
        return false;
    }
    if(readFloatList(data, &values, numberOfValues) == false) {
        return false;
    }

    return true;
}

/**
 * @brief convert message to byte-array
 *
 * @param result reference to the data-buffer to returning the final byte-array
 *
 * @return 0, if data are too big for the provided buffer, else number of used bytes
 */
uint64_t
ClusterIO_Message::createBlob(uint8_t* result, const uint64_t bufferSize)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader)
                                  + 3 * sizeof(Entry)
                                  + segmentName.size()
                                  + sizeof(uint64_t)
                                  + numberOfValues * sizeof(float);

    if(bufferSize < totalMsgSize) {
        return 0;
    }

    uint64_t pos = 0;
    pos += initBlob(&result[pos], totalMsgSize);
    pos += appendString(&result[pos], segmentName);
    pos += appendUint(&result[pos], segmentType);
    pos += appendFloatList(&result[pos], values, numberOfValues);

    assert(pos == totalMsgSize);

    return pos;
}

//==================================================================================================

/**
 * @brief constructor
 */
RequestStart_Message::RequestStart_Message()
{
    m_type = 2;
}

/**
 * @brief destructor
 */
RequestStart_Message::~RequestStart_Message() {}

/**
 * @brief read message from byte-array
 *
 * @param data pointer to byte-buffer
 * @param dataSize number of bytes
 *
 * @return true, if message was valid, else false
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
 * @brief convert message to byte-array
 *
 * @param result reference to the data-buffer to returning the final byte-array
 */
uint64_t
RequestStart_Message::createBlob(uint8_t* result, const uint64_t bufferSize)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader);
    if(bufferSize < totalMsgSize) {
        return 0;
    }

    uint64_t pos = 0;
    pos += initBlob(&result[pos], totalMsgSize);

    assert(pos == totalMsgSize);

    return pos;
}

//==================================================================================================

/**
 * @brief constructor
 */
LearnStart_Message::LearnStart_Message()
{
    m_type = 3;
}

/**
 * @brief destructor
 */
LearnStart_Message::~LearnStart_Message() {}

/**
 * @brief read message from byte-array
 *
 * @param data pointer to byte-buffer
 * @param dataSize number of bytes
 *
 * @return true, if message was valid, else false
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
 * @brief convert message to byte-array
 *
 * @param result reference to the data-buffer to returning the final byte-array
 */
uint64_t
LearnStart_Message::createBlob(uint8_t* result, const uint64_t bufferSize)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader);
    if(bufferSize < totalMsgSize) {
        return 0;
    }

    uint64_t pos = 0;
    pos += initBlob(result, totalMsgSize);

    assert(pos == totalMsgSize);

    return pos;
}

//==================================================================================================

/**
 * @brief constructor
 */
RequestEnd_Message::RequestEnd_Message()
{
    m_type = 4;
}

/**
 * @brief destructor
 */
RequestEnd_Message::~RequestEnd_Message() {}

/**
 * @brief read message from byte-array
 *
 * @param data pointer to byte-buffer
 * @param dataSize number of bytes
 *
 * @return true, if message was valid, else false
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
 * @brief convert message to byte-array
 *
 * @param result reference to the data-buffer to returning the final byte-array
 */
uint64_t
RequestEnd_Message::createBlob(uint8_t* result, const uint64_t bufferSize)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader);
    if(bufferSize < totalMsgSize) {
        return 0;
    }

    uint64_t pos = 0;
    pos += initBlob(result, totalMsgSize);

    assert(pos == totalMsgSize);

    return pos;
}

//==================================================================================================

/**
 * @brief constructor
 */
LearnEnd_Message::LearnEnd_Message()
{
    m_type = 5;
}

/**
 * @brief destructor
 */
LearnEnd_Message::~LearnEnd_Message() {}

/**
 * @brief read message from byte-array
 *
 * @param data pointer to byte-buffer
 * @param dataSize number of bytes
 *
 * @return true, if message was valid, else false
 */
bool
LearnEnd_Message::read(void* data, const uint64_t dataSize)
{
    if(initRead(data, dataSize) == false) {
        return false;
    }

    return true;
}

/**
 * @brief convert message to byte-array
 *
 * @param result reference to the data-buffer to returning the final byte-array
 */
uint64_t
LearnEnd_Message::createBlob(uint8_t* result, const uint64_t bufferSize)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader);
    if(bufferSize < totalMsgSize) {
        return 0;
    }

    uint64_t pos = 0;
    pos += initBlob(result, totalMsgSize);

    assert(pos == totalMsgSize);

    return pos;
}

//==================================================================================================

}  // namespace Hanami
}  // namespace Kitsunemimi
