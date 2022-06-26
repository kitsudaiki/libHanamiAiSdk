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
 * @brief convert message to byte-array
 *
 * @param result reference to the data-buffer to returning the final byte-array
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
void
RequestStart_Message::createBlob(DataBuffer &result)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader);
    initBlob(result, totalMsgSize);
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
void
LearnStart_Message::createBlob(DataBuffer &result)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader);
    initBlob(result, totalMsgSize);
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
void
RequestEnd_Message::createBlob(DataBuffer &result)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader);
    initBlob(result, totalMsgSize);
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
void
LearnEnd_Message::createBlob(DataBuffer &result)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader);
    initBlob(result, totalMsgSize);
}

//==================================================================================================

}  // namespace Hanami
}  // namespace Kitsunemimi
