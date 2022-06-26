/**
 * @file        io.cpp
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

#include <libKitsunemimiHanamiSdk/io.h>

#include <libKitsunemimiHanamiSdk/messages/hanami_messages.h>
#include <libKitsunemimiHanamiSdk/common/websocket_client.h>

namespace Kitsunemimi
{
namespace Hanami
{

/**
 * @brief learn learn single value
 *
 * @param wsClient pointer to websocket-client for data-transfer
 * @param inputValues float-pointer to array with input-values for input-segment
 * @param numberOfInputValues number of input-values for input-segment
 * @param shouldValues float-pointer to array with should-values for output-segment
 * @param numberOfShouldValues number of should-values for output-segment
 * @param error reference for error-output
 *
 * @return true, if successful, else false
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
    if(wsClient->sendMessage(inputBuffer.data, inputBuffer.usedBufferSize, error) == false)
    {
        error.addMeesage("Failed to send input-values");
        LOG_ERROR(error);
        return false;
    }

    // send should
    if(wsClient->sendMessage(shouldBuffer.data, shouldBuffer.usedBufferSize, error) == false)
    {
        error.addMeesage("Failed to send should-values");
        LOG_ERROR(error);
        return false;
    }

    // send start of learn
    Kitsunemimi::Hanami::LearnStart_Message learnStartMsg;
    learnStartMsg.createBlob(buffer);
    if(wsClient->sendMessage(buffer.data, buffer.usedBufferSize, error) == false)
    {
        error.addMeesage("Failed to send learn-start-message");
        LOG_ERROR(error);
        return false;
    }

    // receive response
    uint64_t numberOfBytes = 0;
    uint8_t* recvData = wsClient->readMessage(numberOfBytes, error);
    if(recvData == nullptr
            || numberOfBytes == 0)
    {
        error.addMeesage("Got no valid response");
        LOG_ERROR(error);
        return false;
    }

    // check end-message
    bool success = true;
    Kitsunemimi::Hanami::LearnEnd_Message recvMsg;
    if(recvMsg.read(recvData, numberOfBytes) == false)
    {
        success = false;
        error.addMeesage("Got no valid learn-end-message");
        LOG_ERROR(error);
    }

    delete[] recvData;

    return success;
}

/**
 * @brief request request single value
 *
 * @param wsClient pointer to websocket-client for data-transfer
 * @param inputValues float-pointer to array with input-values for input-segment
 * @param numberOfInputValues number of input-values for input-segment
 * @param numberOfOutputValues reference for returning number of output-values
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
float*
request(Kitsunemimi::Hanami::WebsocketClient* wsClient,
        float* inputData,
        const uint64_t numberOfInputValues,
        uint64_t &numberOfOutputValues,
        Kitsunemimi::ErrorContainer &error)
{
    Kitsunemimi::DataBuffer buffer;
    Kitsunemimi::DataBuffer inputBuffer;

    Kitsunemimi::Hanami::ClusterIO_Message inputMsg;
    inputMsg.segmentType = Kitsunemimi::Hanami::ClusterIO_Message::INPUT_SEGMENT;
    inputMsg.segmentId = 0;
    inputMsg.values = inputData;
    inputMsg.numberOfValues = numberOfInputValues;
    inputMsg.createBlob(inputBuffer);

    // send input
    if(wsClient->sendMessage(inputBuffer.data, inputBuffer.usedBufferSize, error) == false)
    {
        error.addMeesage("Failed to send input-values");
        LOG_ERROR(error);
        return nullptr;
    }

    // send start of request
    Kitsunemimi::Hanami::RequestStart_Message reqStartMsg;
    reqStartMsg.createBlob(buffer);
    if(wsClient->sendMessage(buffer.data, buffer.usedBufferSize, error) == false)
    {
        error.addMeesage("Failed to send request-start-message");
        LOG_ERROR(error);
        return nullptr;
    }

    // receive response
    uint64_t numberOfBytes = 0;
    uint8_t* recvData = wsClient->readMessage(numberOfBytes, error);
    if(recvData == nullptr
            || numberOfBytes == 0)
    {
        error.addMeesage("Got no valid request response");
        LOG_ERROR(error);
        return nullptr;
    }

    // read message from response
    Kitsunemimi::Hanami::ClusterIO_Message recvMsg;
    if(recvMsg.read(recvData, numberOfBytes) == false)
    {
        delete[] recvData;
        error.addMeesage("Got no valid request response");
        LOG_ERROR(error);
        return nullptr;
    }

    // convert output
    numberOfOutputValues = recvMsg.numberOfValues;
    float* result = new float[numberOfOutputValues];
    for(uint64_t i = 0; i < numberOfOutputValues; i++) {
        result[i] = recvMsg.values[i];
    }

    delete[] recvData;

    return result;
}

} // namespace Hanami
} // namespace Kitsunemimi
