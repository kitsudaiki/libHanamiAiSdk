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

#include <libHanamiAiSdk/task.h>
#include <common/http_client.h>

namespace Kitsunemimi
{
namespace Hanami
{

/**
 * @brief create a new learn-task
 *
 * @param result reference for response-message
 * @param clusterUuid uuid of the cluster, which should execute the task
 * @param dataSetUuid uuid of the data-set-file on server
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
createImageLearnTask(std::string &result,
                     const std::string &name,
                     const std::string &clusterUuid,
                     const std::string &dataSetUuid,
                     ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/task/image/learn";
    const std::string vars = "";
    const std::string jsonBody = "{\"name\":\""
                                 + name
                                 + "\",\"cluster_uuid\":\""
                                 + clusterUuid
                                 + "\",\"data_set_uuid\":\""
                                 + dataSetUuid
                                 + "\"}";

    // send request
    if(request->sendPostRequest(result, path, vars, jsonBody, error) == false)
    {
        error.addMeesage("Failed to start image-learn-task on cluster with UUID '"
                         + clusterUuid
                         + "' and dataset with UUID '"
                         + dataSetUuid
                         + "'");
        LOG_ERROR(error);
        return false;
    }

    return true;
}

/**
 * @brief create a new request-task
 *
 * @param result reference for response-message
 * @param clusterUuid uuid of the cluster, which should execute the task
 * @param dataSetUuid uuid of the data-set-file on server
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
createImageRequestTask(std::string &result,
                       const std::string &name,
                       const std::string &clusterUuid,
                       const std::string &dataSetUuid,
                       ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/task/image/request";
    const std::string vars = "";
    const std::string jsonBody = "{\"name\":\""
                                 + name
                                 + "\",\"cluster_uuid\":\""
                                 + clusterUuid
                                 + "\",\"data_set_uuid\":\""
                                 + dataSetUuid
                                 + "\"}";

    // send request
    if(request->sendPostRequest(result, path, vars, jsonBody, error) == false)
    {
        error.addMeesage("Failed to start image-request-task on cluster with UUID '"
                         + clusterUuid
                         + "' and dataset with UUID '"
                         + dataSetUuid
                         + "'");
        LOG_ERROR(error);
        return false;
    }

    return true;
}

/**
 * @brief create a new learn-task
 *
 * @param result reference for response-message
 * @param clusterUuid uuid of the cluster, which should execute the task
 * @param dataSetUuid uuid of the data-set-file on server
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
createGraphLearnTask(std::string &result,
                     const std::string &name,
                     const std::string &clusterUuid,
                     const std::string &dataSetUuid,
                     const std::string &columnName,
                     ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/task/graph/learn";
    const std::string vars = "";
    const std::string jsonBody = "{\"name\":\""
                                 + name
                                 + "\",\"cluster_uuid\":\""
                                 + clusterUuid
                                 + "\",\"data_set_uuid\":\""
                                 + dataSetUuid
                                 + "\",\"column_name\":\""
                                 + columnName
                                 + "\"}";

    // send request
    if(request->sendPostRequest(result, path, vars, jsonBody, error) == false)
    {
        error.addMeesage("Failed to start graph-learn-task on cluster with UUID '"
                         + clusterUuid
                         + "' and dataset with UUID '"
                         + dataSetUuid
                         + "'");
        LOG_ERROR(error);
        return false;
    }

    return true;
}

/**
 * @brief create a new request-task
 *
 * @param result reference for response-message
 * @param clusterUuid uuid of the cluster, which should execute the task
 * @param dataSetUuid uuid of the data-set-file on server
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
createGraphRequestTask(std::string &result,
                       const std::string &name,
                       const std::string &clusterUuid,
                       const std::string &dataSetUuid,
                       const std::string &columnName,
                       ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/task/graph/request";
    const std::string vars = "";
    const std::string jsonBody = "{\"name\":\""
                                 + name
                                 + "\",\"cluster_uuid\":\""
                                 + clusterUuid
                                 + "\",\"data_set_uuid\":\""
                                 + dataSetUuid
                                 + "\",\"column_name\":\""
                                 + columnName
                                 + "\"}";

    // send request
    if(request->sendPostRequest(result, path, vars, jsonBody, error) == false)
    {
        error.addMeesage("Failed to start graph-request-task on cluster with UUID '"
                         + clusterUuid
                         + "' and dataset with UUID '"
                         + dataSetUuid
                         + "'");
        LOG_ERROR(error);
        return false;
    }

    return true;
}

/**
 * @brief get task-information
 *
 * @param result reference for response-message
 * @param taskUuid uuid of the requested task
 * @param clusterUuid uuid of the cluster, where the task belongs to
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
getTask(std::string &result,
        const std::string &taskUuid,
        const std::string &clusterUuid,
        ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/task";
    std::string vars = "uuid=" + taskUuid + "&cluster_uuid=" + clusterUuid;

    // send request
    if(request->sendGetRequest(result, path, vars, error) == false)
    {
        error.addMeesage("Failed to get task with UUID '"
                         + taskUuid
                         + "' of cluster with UUID '"
                         + clusterUuid
                         + "'");
        LOG_ERROR(error);
        return false;
    }

    return true;
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
    if(request->sendGetRequest(result, path, "", error) == false)
    {
        error.addMeesage("Failed to list tasks");
        LOG_ERROR(error);
        return false;
    }

    return true;
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
    if(request->sendDeleteRequest(result, path, vars, error) == false)
    {
        error.addMeesage("Failed to delete task with UUID '" + taskUuid + "'");
        LOG_ERROR(error);
        return false;
    }

    return true;
}

} // namespace Hanami
} // namespace Kitsunemimi
