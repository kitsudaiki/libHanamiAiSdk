/**
 * @file        data_set.cpp
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

#include <libKitsunemimiHanamiSdk/actions/data_set.h>

#include <libKitsunemimiCrypto/common.h>
#include <libKitsunemimiJson/json_item.h>
#include <libKitsunemimiCommon/common_items/data_items.h>

#include <libKitsunemimiSakuraNetwork/session_controller.h>
#include <libKitsunemimiSakuraNetwork/session.h>

namespace Kitsunemimi
{
namespace Hanami
{

/**
 * @brief get size of a local file
 *
 * @param filePath path the file to check
 *
 * @return size of file if successful, or -1 if failed
 */
long
getFileSize(const std::string &filePath)
{
    std::ifstream in(filePath, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

/**
 * @brief initialize a new csv-dataset in sagiri
 *
 * @param result reference for response-message
 * @param dataSetName name for the new data-set
 * @param inputDataSize size of the file with the input-data
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
createCsvDataSet(std::string &result,
                 const std::string &dataSetName,
                 const uint64_t inputDataSize,
                 ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/sagiri/v1/csv/data_set";
    const std::string vars = "";
    const std::string jsonBody = "{\"name\":\""    + dataSetName + "\""
                                 ",\"input_data_size\":" + std::to_string(inputDataSize) + "}";

    // send request
    if(request->sendPostRequest(result, path, vars, jsonBody, error) == false) {
        return false;
    }

    return true;
}

/**
 * @brief finalize data-set
 *
 * @param result reference for response-message
 * @param uuid uuid to identify the data-set
 * @param inputUuid uuid to identify the temporary file with the input-data on server-side
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
finalizeCsvDataSet(std::string &result,
                   const std::string &uuid,
                   const std::string &inputUuid,
                   ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/sagiri/v1/csv/data_set";
    const std::string vars = "";
    const std::string jsonBody = "{\"uuid\":\""    + uuid + "\""
                                 ",\"uuid_input_file\":\"" + inputUuid + "\"}";

    // send request
    if(request->sendPutRequest(result, path, vars, jsonBody, error) == false) {
        return false;
    }

    return true;
}

/**
 * @brief initialize a new mnist-dataset in sagiri
 *
 * @param result reference for response-message
 * @param dataSetName name for the new data-set
 * @param inputDataSize size of the file with the input-data
 * @param labelDataSize  size of the file with the label-data
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
createMnistDataSet(std::string &result,
                   const std::string &dataSetName,
                   const uint64_t inputDataSize,
                   const uint64_t labelDataSize,
                   ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/sagiri/v1/mnist/data_set";
    const std::string vars = "";
    const std::string jsonBody = "{\"name\":\""    + dataSetName + "\""
                                 ",\"input_data_size\":" + std::to_string(inputDataSize) +
                                 ",\"label_data_size\":" + std::to_string(labelDataSize) + "}";

    // send request
    if(request->sendPostRequest(result, path, vars, jsonBody, error) == false) {
        return false;
    }

    return true;
}

/**
 * @brief finalize data-set
 *
 * @param result reference for response-message
 * @param uuid uuid to identify the data-set
 * @param inputUuid uuid to identify the temporary file with the input-data on server-side
 * @param labelUuid uuid to identify the temporary file with the label-data on server-side
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
finalizeMnistDataSet(std::string &result,
                     const std::string &uuid,
                     const std::string &inputUuid,
                     const std::string &labelUuid,
                     ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/sagiri/v1/mnist/data_set";
    const std::string vars = "";
    const std::string jsonBody = "{\"uuid\":\""    + uuid + "\""
                                 ",\"uuid_input_file\":\"" + inputUuid + "\""
                                 ",\"uuid_label_file\":\"" + labelUuid + "\"}";

    // send request
    if(request->sendPutRequest(result, path, vars, jsonBody, error) == false) {
        return false;
    }

    return true;
}

/**
 * @brief send data to sagiri
 *
 * @param session session over which the data should be send
 * @param uuid uuid of the file for identification in sagiri
 * @param filePath path to file, which should be send
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
sendFile(Sakura::Session* session,
         const std::string &uuid,
         const std::string &filePath,
         ErrorContainer &error)
{
    // get data, which should be send
    const uint64_t dataSize = getFileSize(filePath);
    Kitsunemimi::BinaryFile sourceFile(filePath);

    bool success = true;
    uint64_t i = 0;

    // prepare buffer
    uint64_t segmentSize = 96 * 1024;
    uint8_t* sendBuffer = new uint8_t[128*1024];
    memcpy(sendBuffer, uuid.c_str(), 36);

    do
    {
        memcpy(&sendBuffer[36], &i, 8);

        // check the size for the last segment
        segmentSize = 96 * 1024;
        if(dataSize - i < segmentSize) {
            segmentSize = dataSize - i;
        }

        // read segment of the local file
        if(sourceFile.readDataFromFile(&sendBuffer[44], i, segmentSize) == false)
        {
            success = false;
            error.addMeesage("Failed to read file '" + filePath + "'");
            break;
        }

        // send segment
        if(session->sendStreamData(sendBuffer, segmentSize + 44, error) == false)
        {
            success = false;
            break;
        }

        i += segmentSize;
    }
    while(i < dataSize);

    delete[] sendBuffer;
    return success;
}

/**
 * @brief upload new csv-data-set to sagiri
 *
 * @param result reference for response-message
 * @param dataSetName name for the new data-set
 * @param inputFilePath path to file with the inputs
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
uploadCsvData(std::string &result,
              const std::string &dataSetName,
              const std::string &inputFilePath,
              ErrorContainer &error)
{
    // init new mnist-data-set
    if(createCsvDataSet(result,
                        dataSetName,
                        getFileSize(inputFilePath),
                        error) == false)
    {
        return false;
    }

    // parse output to get the uuid
    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return false;
    }

    // get ids from inital reponse to identify the file-transfer
    const std::string uuid = jsonItem.get("uuid").getString();
    const std::string inputUuid = jsonItem.get("uuid_input_file").getString();

    HanamiRequest* request = HanamiRequest::getInstance();
    Sakura::Session* session = request->createSakuraSession("sagiri", error);
    if(session == nullptr)
    {
        LOG_ERROR(error);
        return false;
    }

    // send files
    if(sendFile(session, inputUuid, inputFilePath, error) == false) {
        return false;
    }

    // TODO: check via rest-api-call, if files are complete on server-side
    sleep(1);

    if(finalizeCsvDataSet(result, uuid, inputUuid, error) == false) {
        return false;
    }

    session->closeSession(error);
    // wait a second for the cleaner-thread to fully close the session
    sleep(1);

    return true;
}

/**
 * @brief upload new mnist-data-set to sagiri
 *
 * @param result reference for response-message
 * @param dataSetName name for the new data-set
 * @param inputFilePath path to file with the inputs
 * @param labelFilePath path to file with the labels
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
uploadMnistData(std::string &result,
                const std::string &dataSetName,
                const std::string &inputFilePath,
                const std::string &labelFilePath,
                ErrorContainer &error)
{
    // init new mnist-data-set
    if(createMnistDataSet(result,
                          dataSetName,
                          getFileSize(inputFilePath),
                          getFileSize(labelFilePath),
                          error) == false)
    {
        return false;
    }

    // parse output to get the uuid
    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return false;
    }

    // get ids from inital reponse to identify the file-transfer
    const std::string uuid = jsonItem.get("uuid").getString();
    const std::string inputUuid = jsonItem.get("uuid_input_file").getString();
    const std::string labelUuid = jsonItem.get("uuid_label_file").getString();

    HanamiRequest* request = HanamiRequest::getInstance();
    Sakura::Session* session = request->createSakuraSession("sagiri", error);
    if(session == nullptr)
    {
        LOG_ERROR(error);
        return false;
    }

    // send files
    if(sendFile(session, inputUuid, inputFilePath, error) == false) {
        return false;
    }
    if(sendFile(session, labelUuid, labelFilePath, error) == false) {
        return false;
    }

    // TODO: check via rest-api-call, if files are complete on server-side
    sleep(1);

    if(finalizeMnistDataSet(result, uuid, inputUuid, labelUuid, error) == false) {
        return false;
    }

    session->closeSession(error);
    // wait a second for the cleaner-thread to fully close the session
    sleep(1);

    return true;
}

/**
 * @brief check values against a data-set to get correctness
 *
 * @param result reference for response-message
 * @param resultUuid uuid of the result-set to compare
 * @param dataUuid uuid of the data-set to compare to
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
checkDataset(std::string &result,
             const std::string &resultUuid,
             const std::string &dataUuid,
             ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/sagiri/v1/data_set/check";
    const std::string vars = "";
    const std::string jsonBody = "{\"data_set_uuid\":\"" + dataUuid + "\""
                                 ",\"result_uuid\":\"" + resultUuid + "\"}";

    // send request
    if(request->sendPostRequest(result, path, vars, jsonBody, error) == false) {
        return false;
    }

    return true;
}

/**
 * @brief get metadata of a specific data-set
 *
 * @param result reference for response-message
 * @param dataUuid uuid of the requested data-set
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
getDataset(std::string &result,
           const std::string &dataUuid,
           ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/sagiri/v1/data_set";
    const std::string vars = "uuid=" + dataUuid;

    // send request
    return request->sendGetRequest(result, path, vars, error);
}

/**
 * @brief list all data-sets of the user, which are available on sagiri
 *
 * @param result reference for response-message
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
listDatasets(std::string &result,
             ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/sagiri/v1/data_set/all";

    // send request
    return request->sendGetRequest(result, path, "", error);
}

/**
 * @brief delete a data-set from sagiri
 *
 * @param result reference for response-message
 * @param dataUuid uuid of the data-set to delete
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
deleteDataset(std::string &result,
              const std::string &dataUuid,
              ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/sagiri/v1/data_set";
    const std::string vars = "uuid=" + dataUuid;

    // send request
    return request->sendDeleteRequest(result, path, vars, error);
}

} // namespace Hanami
} // namespace Kitsunemimi
