/**
 * @file        task.cpp
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

#include <libKitsunemimiHanamiSdk/actions/task.h>

namespace Kitsunemimi
{
namespace Hanami
{

/**
 * @brief create a new learn-task
 *
 * @param result reference for response-message
 * @param clusterUuid uuid of the cluster, which should execute the task
 * @param inputsUuid uuid of the input-file on server
 * @param labelsUuid uuid of the label-file on server
 * @param type type of the data
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
createLearnTask(std::string &result,
                const std::string &clusterUuid,
                const std::string &inputsUuid,
                const std::string &labelsUuid,
                const std::string &type,
                ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/task/learn";
    const std::string vars = "";
    const std::string jsonBody = "{\"cluster_uuid\":\""
                                 + clusterUuid
                                 + "\",\"input_data_uuid\":\""
                                 + inputsUuid
                                 + "\",\"label_data_uuid\":\""
                                 + labelsUuid
                                 + "\",\"type\":\""
                                 + type
                                 + "\"}";

    // send request
    return request->sendPostRequest(result, path, vars, jsonBody, error);
}

/**
 * @brief create a new request-task
 *
 * @param result reference for response-message
 * @param clusterUuid uuid of the cluster, which should execute the task
 * @param inputsUuid uuid of the input-file on server
 * @param type type of the data
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
createRequestTask(std::string &result,
                  const std::string &clusterUuid,
                  const std::string &inputsUuid,
                  const std::string &type,
                  ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/task/request";
    const std::string vars = "";
    const std::string jsonBody = "{\"cluster_uuid\":\""
                                 + clusterUuid
                                 + "\",\"input_data_uuid\":\""
                                 + inputsUuid
                                 + "\",\"type\":\""
                                 + type
                                 + "\"}";

    // send request
    return request->sendPostRequest(result, path, vars, jsonBody, error);
}

/**
 * @brief get task-information
 *
 * @param result reference for response-message
 * @param taskUuid uuid of the requested task
 * @param clusterUuid uuid of the cluster, where the task belongs to
 * @param withResult set to trus, if also result should be returned in case that the task is finish
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
getTask(std::string &result,
        const std::string &taskUuid,
        const std::string &clusterUuid,
        const bool withResult,
        ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/task";
    std::string vars = "uuid=" + taskUuid + "&cluster_uuid=" + clusterUuid;

    // in case the result of the task should be retruned as well
    if(withResult) {
        vars.append("&with_result=true");
    }

    // send request
    return request->sendGetRequest(result, path, vars, error);
}

/**
 * @brief list all visible tasks on kyouko
 *
 * @param result reference for response-message
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
listTask(std::string &result,
         ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/task/all";

    // send request
    return request->sendGetRequest(result, path, "", error);
}

/**
 * @brief delete or abort a task from kyouko
 *
 * @param result reference for response-message
 * @param taskUuid uuid of the task, which should be deleted
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
deleteTask(std::string &result,
           const std::string &taskUuid,
           ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/task";
    const std::string vars = "uuid=" + taskUuid;

    // send request
    return request->sendDeleteRequest(result, path, vars, error);
}

} // namespace Hanami
} // namespace Kitsunemimi
