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

#include <../../libKitsunemimiHanamiProtobuffers/kyouko_messages.proto3.pb.h>

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

    ClusterIO_Message inputMsg;
    inputMsg.set_segmentname("input");
    inputMsg.set_islast(false);
    inputMsg.set_processtype(ClusterProcessType::LEARN_TYPE);
    inputMsg.set_datatype(ClusterDataType::INPUT_TYPE);
    inputMsg.set_numberofvalues(numberOfInputValues);
    for(uint64_t i = 0; i < numberOfInputValues; i++) {
        inputMsg.add_values(inputValues[i]);
    }

    const uint64_t inputMsgSize = inputMsg.ByteSizeLong();
    if(inputMsg.SerializeToArray(buffer, inputMsgSize) == false)
    {
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

    ClusterIO_Message shouldMsg;
    shouldMsg.set_segmentname("output");
    shouldMsg.set_islast(true);
    shouldMsg.set_processtype(ClusterProcessType::LEARN_TYPE);
    shouldMsg.set_datatype(ClusterDataType::SHOULD_TYPE);
    shouldMsg.set_numberofvalues(numberOfShouldValues);
    for(uint64_t i = 0; i < numberOfShouldValues; i++) {
        shouldMsg.add_values(shouldValues[i]);
    }

    const uint64_t shouldMsgSize = shouldMsg.ByteSizeLong();
    if(shouldMsg.SerializeToArray(buffer, shouldMsgSize) == false)
    {
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
    if(response.ParseFromArray(recvData, numberOfBytes) == false)
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

    ClusterIO_Message inputMsg;
    inputMsg.set_segmentname("input");
    inputMsg.set_islast(true);
    inputMsg.set_processtype(ClusterProcessType::REQUEST_TYPE);
    inputMsg.set_datatype(ClusterDataType::INPUT_TYPE);
    inputMsg.set_numberofvalues(numberOfInputValues);
    for(uint64_t i = 0; i < numberOfInputValues; i++) {
        inputMsg.add_values(inputData[i]);
    }

    const uint64_t inputMsgSize = inputMsg.ByteSizeLong();
    if(inputMsg.SerializeToArray(buffer, inputMsgSize) == false)
    {
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
    if(response.ParseFromArray(recvData, numberOfBytes) == false)
    {
        delete[] recvData;
        error.addMeesage("Got no valid request response");
        LOG_ERROR(error);
        return nullptr;
    }

    // convert output
    numberOfOutputValues = response.numberofvalues();
    float* result = new float[numberOfOutputValues];
    for(uint64_t i = 0; i < numberOfOutputValues; i++) {
        result[i] = response.values(i);
    }

    delete[] recvData;

    return result;
}

} // namespace Hanami
} // namespace Kitsunemimi
