#include <libKitsunemimiHanamiSdk/actions/cluster.h>

#include <libKitsunemimiCrypto/common.h>
#include <libKitsunemimiJson/json_item.h>

namespace Kitsunemimi
{
namespace Hanami
{

long
getFileSize(const std::string &filePath)
{
    std::ifstream in(filePath, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

bool
createTrainData(std::string &result,
                const std::string &dataName,
                const std::string &dataType,
                const uint64_t dataSize,
                ErrorContainer &error)
{

    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/sagiri/v1/train_data";
    const std::string vars = "";
    const std::string jsonBody = "{\"name\":\""    + dataName + "\""
                                 ",\"type\":\""    + dataType + "\""
                                 ",\"data_size\":" + std::to_string(dataSize) + "}";

    if(request->sendPostRequest(result, path, vars, jsonBody, error) == false) {
        return false;
    }

    return true;
}

bool
sendDataBlock(std::string &result,
              const std::string &uuid,
              const uint64_t position,
              const std::string &data,
              ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/sagiri/v1/train_data";
    const std::string vars = "";
    const std::string jsonBody = "{\"uuid\":\""   + uuid  + "\""
                                 ",\"position\":" + std::to_string(position) + ""
                                 ",\"data\":\""   + data + "\"}";

    if(request->sendPutRequest(result, path, vars, jsonBody, error) == false) {
        return false;
    }

    return true;
}

bool
uploadTrainData(std::string &result,
                const std::string &dataName,
                const std::string &dataType,
                const std::string &localFilePath,
                ErrorContainer &error)
{
    const uint64_t dataSize = getFileSize(localFilePath);

    if(createTrainData(result, dataName, dataType, dataSize, error) == false) {
        return false;
    }

    Kitsunemimi::BinaryFile requestInputFile(localFilePath);
    // parse output
    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return false;
    }
    const std::string uuid = jsonItem.get("uuid").getString();

    uint64_t i = 0;
    const uint64_t numberOfSegmentsPerSent = 128;
    uint64_t segmentSize = numberOfSegmentsPerSent * 4096;
    do
    {
        if(dataSize - i < segmentSize) {
            segmentSize = dataSize - i;
        }

        std::string base64Segment;
        DataBuffer segment(numberOfSegmentsPerSent);
        segment.usedBufferSize = segmentSize;
        if(requestInputFile.readSegment(segment, i, segmentSize) == false) {
            return false;
        }
        Kitsunemimi::Crypto::encodeBase64(base64Segment, segment.data, segmentSize);

        std::string putResult;
        if(sendDataBlock(putResult, uuid, i, base64Segment, error) == false) {
            return false;
        }

        i += segmentSize;
    }
    while(i < dataSize);

    requestInputFile.closeFile();

    return true;
}

bool
getTrainData(std::string &result,
             const std::string &dataUuid,
             ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/sagiri/v1/train_data";
    const std::string vars = "uuid=" + dataUuid;

    return request->sendGetRequest(result, path, vars, error);
}

bool
listTrainData(std::string &result,
              ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/sagiri/v1/train_data/all";

    return request->sendGetRequest(result, path, "", error);
}

bool
deleteTrainData(std::string &result,
                const std::string &dataUuid,
                ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/sagiri/v1/train_data";
    const std::string vars = "uuid=" + dataUuid;

    return request->sendDeleteRequest(result, path, vars, error);
}

}
}
