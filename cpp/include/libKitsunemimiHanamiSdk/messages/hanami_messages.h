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

}  // namespace Hanami
}  // namespace Kitsunemimi

#endif // HANAMIMESSAGES_H
