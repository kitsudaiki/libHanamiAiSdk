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

#include <libKitsumiAiSdk/io.h>

#include <libKitsumiAiSdk/common/websocket_client.h>

#include <../../libKitsunemimiHanamiMessages/hanami_messages/kyouko_messages.h>

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
    uint8_t buffer[96*1024];

    Kitsunemimi::Hanami::ClusterIO_Message inputMsg;
    inputMsg.segmentName = "input";
    inputMsg.isLast = false;
    inputMsg.processType = Kitsunemimi::Hanami::ClusterIO_Message::ProcessType::LEARN_TYPE;
    inputMsg.dataType = Kitsunemimi::Hanami::ClusterIO_Message::DataType::INPUT_TYPE;
    inputMsg.numberOfValues = numberOfInputValues;
    inputMsg.values = inputValues;

    const uint64_t inputMsgSize = inputMsg.createBlob(buffer, 96*1024);
    if(inputMsgSize == 0)
    {
        Kitsunemimi::ErrorContainer error;
        error.addMeesage("Failed to serialize learn-message");
        return false;
    }

    // send input
    if(wsClient->sendMessage(buffer, inputMsgSize, error) == false)
    {
        error.addMeesage("Failed to send input-values");
        LOG_ERROR(error);
        return false;
    }

    Kitsunemimi::Hanami::ClusterIO_Message shouldMsg;
    shouldMsg.segmentName = "output";
    shouldMsg.isLast = true;
    shouldMsg.processType = Kitsunemimi::Hanami::ClusterIO_Message::ProcessType::LEARN_TYPE;
    shouldMsg.dataType = Kitsunemimi::Hanami::ClusterIO_Message::DataType::SHOULD_TYPE;
    shouldMsg.numberOfValues = numberOfShouldValues;
    shouldMsg.values = shouldValues;

    const uint64_t shouldMsgSize = shouldMsg.createBlob(buffer, 96*1024);
    if(shouldMsgSize == 0)
    {
        Kitsunemimi::ErrorContainer error;
        error.addMeesage("Failed to serialize learn-message");
        return false;
    }

    // send should
    if(wsClient->sendMessage(buffer, shouldMsgSize, error) == false)
    {
        error.addMeesage("Failed to send should-values");
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
    ClusterIO_Message response;
    if(response.read(recvData, numberOfBytes) == false)
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
    uint8_t buffer[96*1024];

    Kitsunemimi::Hanami::ClusterIO_Message inputMsg;
    inputMsg.segmentName = "input";
    inputMsg.isLast = true;
    inputMsg.processType = Kitsunemimi::Hanami::ClusterIO_Message::ProcessType::REQUEST_TYPE;
    inputMsg.dataType = Kitsunemimi::Hanami::ClusterIO_Message::DataType::INPUT_TYPE;
    inputMsg.numberOfValues = numberOfInputValues;
    inputMsg.values = inputData;

    const uint64_t inputMsgSize = inputMsg.createBlob(buffer, 96*1024);
    if(inputMsgSize == 0)
    {
        Kitsunemimi::ErrorContainer error;
        error.addMeesage("Failed to serialize request-message");
        return nullptr;
    }

    // send input
    if(wsClient->sendMessage(buffer, inputMsgSize, error) == false)
    {
        error.addMeesage("Failed to send input-values");
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
    ClusterIO_Message response;
    if(response.read(recvData, numberOfBytes) == false)
    {
        delete[] recvData;
        error.addMeesage("Got no valid request response");
        LOG_ERROR(error);
        return nullptr;
    }

    // convert output
    numberOfOutputValues = response.numberOfValues;
    float* result = new float[numberOfOutputValues];
    memcpy(result, response.values, numberOfOutputValues * sizeof(float));

    delete[] recvData;

    return result;
}

} // namespace Hanami
} // namespace Kitsunemimi
