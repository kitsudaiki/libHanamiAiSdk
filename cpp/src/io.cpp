#include <libKitsunemimiHanamiSdk/io.h>

#include <libKitsunemimiHanamiSdk/messages/hanami_messages.h>
#include <libKitsunemimiHanamiSdk/common/websocket_client.h>

namespace Kitsunemimi
{
namespace Hanami
{

/**
 * @brief learn
 * @param clusterUuid
 * @param inputData
 * @param numberOfInputValues
 * @param shouldOutputData
 * @param numberOfOutputalues
 * @return
 */
bool
learn(Kitsunemimi::Hanami::WebsocketClient* wsClient,
      float* inputValues,
      const uint64_t numberOfInputValues,
      float* shouldValues,
      const uint64_t numberOfShouldValues,
      Kitsunemimi::ErrorContainer &error)
{
    Kitsunemimi::DataBuffer buffer;
    Kitsunemimi::Hanami::ClusterIO_Message inputMsg;
    Kitsunemimi::Hanami::ClusterIO_Message shouldMsg;
    Kitsunemimi::DataBuffer inputBuffer;
    Kitsunemimi::DataBuffer shouldBuffer;

    inputMsg.segmentType = Kitsunemimi::Hanami::ClusterIO_Message::INPUT_SEGMENT;
    inputMsg.segmentId = 0;
    inputMsg.values = inputValues;
    inputMsg.numberOfValues = numberOfInputValues;
    inputMsg.createBlob(inputBuffer);

    shouldMsg.segmentType = Kitsunemimi::Hanami::ClusterIO_Message::OUTPUT_SEGMENT;
    shouldMsg.segmentId = 0;
    shouldMsg.values = shouldValues;
    shouldMsg.numberOfValues = numberOfShouldValues;
    shouldMsg.createBlob(shouldBuffer);

    // send input
    if(wsClient->sendMessage(inputBuffer.data, inputBuffer.usedBufferSize, error) == false) {
        return false;
    }

    // send should
    if(wsClient->sendMessage(shouldBuffer.data, shouldBuffer.usedBufferSize, error) == false) {
        return false;
    }

    // send start of learn
    Kitsunemimi::Hanami::LearnStart_Message learnStartMsg;
    learnStartMsg.createBlob(buffer);
    if(wsClient->sendMessage(buffer.data, buffer.usedBufferSize, error) == false) {
        return false;
    }

    // receive response
    uint64_t numberOfBytes = 0;
    uint8_t* recvData = wsClient->readMessage(numberOfBytes, error);
    if(recvData == nullptr
            || numberOfBytes == 0)
    {
        return false;
    }

    bool success = true;
    Kitsunemimi::Hanami::LearnEnd_Message recvMsg;
    if(recvMsg.read(recvData, numberOfBytes) == false) {
        success = false;
    }

    delete[] recvData;

    return success;
}

/**
 * @brief request
 * @param clusterUuid
 * @param inputData
 * @param numberOfInputValues
 * @param numberOfOutputValues
 * @return
 */
float*
request(Kitsunemimi::Hanami::WebsocketClient* wsClient,
        float* inputData,
        const uint64_t numberOfInputValues,
        uint64_t &numberOfOutputValues,
        Kitsunemimi::ErrorContainer &error)
{
    Kitsunemimi::DataBuffer buffer;

    // send input
    if(wsClient->sendMessage(inputData,
                             numberOfInputValues * sizeof(float),
                             error) == false)
    {
        return nullptr;
    }

    // send start of request
    Kitsunemimi::Hanami::RequestStart_Message reqStartMsg;
    reqStartMsg.createBlob(buffer);
    if(wsClient->sendMessage(buffer.data, buffer.usedBufferSize, error) == false) {
        return nullptr;
    }

    // receive response
    uint64_t numberOfBytes = 0;
    uint8_t* recvData = wsClient->readMessage(numberOfBytes, error);
    if(recvData == nullptr
            || numberOfBytes == 0)
    {
        return nullptr;
    }

    Kitsunemimi::Hanami::ClusterIO_Message recvMsg;
    if(recvMsg.read(recvData, numberOfBytes) == false)
    {
        delete[] recvData;
        return nullptr;
    }

    numberOfOutputValues = recvMsg.numberOfValues;
    float* result = new float[numberOfOutputValues];
    for(uint64_t i = 0; i < numberOfOutputValues; i++) {
        result[i] = recvMsg.values[i];
    }
    //memcpy(result, recvMsg.values, numberOfOutputValues * sizeof(float));

    delete[] recvData;

    return result;
}

} // namespace Hanami
} // namespace Kitsunemimi
