/**
 * @file        hanami_messages.h
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

#ifndef HANAMIMESSAGES_H
#define HANAMIMESSAGES_H

#include <stdint.h>
#include <libKitsunemimiHanamiCommon/messages.h>

namespace Kitsunemimi
{
namespace Hanami
{

class ClusterIO_Message
        : public HanamiMessage
{
public:
    ClusterIO_Message();
    ~ClusterIO_Message();

    enum SegmentType
    {
        UNDEFINED_SEGMENT_TYPE = 0,
        INPUT_SEGMENT = 1,
        OUTPUT_SEGMENT = 2,
    };

    uint64_t segmentType = UNDEFINED_SEGMENT_TYPE;
    uint64_t segmentId = 0;
    float* values = nullptr;
    uint64_t numberOfValues = 0;

    bool read(void* data, const uint64_t dataSize);
    void createBlob(DataBuffer &result);
};

class RequestStart_Message
        : public HanamiMessage
{
public:
    RequestStart_Message();
    ~RequestStart_Message();

    bool read(void* data, const uint64_t dataSize);
    void createBlob(DataBuffer &result);
};

class LearnStart_Message
        : public HanamiMessage
{
public:
    LearnStart_Message();
    ~LearnStart_Message();

    bool read(void* data, const uint64_t dataSize);
    void createBlob(DataBuffer &result);
};

class RequestEnd_Message
        : public HanamiMessage
{
public:
    RequestEnd_Message();
    ~RequestEnd_Message();

    bool read(void* data, const uint64_t dataSize);
    void createBlob(DataBuffer &result);
};

class LearnEnd_Message
        : public HanamiMessage
{
public:
    LearnEnd_Message();
    ~LearnEnd_Message();

    bool read(void* data, const uint64_t dataSize);
    void createBlob(DataBuffer &result);
};

}  // namespace Hanami
}  // namespace Kitsunemimi

#endif // HANAMIMESSAGES_H
