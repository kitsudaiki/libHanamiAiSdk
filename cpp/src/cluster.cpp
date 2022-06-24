/**
 * @file        cluster.cpp
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

#include <libKitsunemimiHanamiSdk/cluster.h>
#include <common/http_client.h>
#include <libKitsunemimiHanamiSdk/common/websocket_client.h>

namespace Kitsunemimi
{
namespace Hanami
{

/**
 * @brief create a new cluster from a template on kyouko
 *
 * @param result reference for response-message
 * @param clusterName name of the new cluster
 * @param templateUuid uuid of the template, which works as base for the new cluster
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
createCluster(std::string &result,
              const std::string &clusterName,
              const std::string &templateUuid,
              ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/cluster";
    const std::string vars = "";
    const std::string jsonBody = "{\"name\":\""
                                 + clusterName
                                 + "\",\"template_uuid\":\""
                                 + templateUuid
                                 + "\"}";

    // send request
    return request->sendPostRequest(result, path, vars, jsonBody, error);
}

/**
 * @brief get information of a cluster from kyouko
 *
 * @param result reference for response-message
 * @param clusterUuid uuid of the cluster to get
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
getCluster(std::string &result,
           const std::string &clusterUuid,
           ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/cluster";
    const std::string vars = "uuid=" + clusterUuid;

    // send request
    return request->sendGetRequest(result, path, vars, error);
}

/**
 * @brief list all visible cluster on kyouko
 *
 * @param result reference for response-message
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
listCluster(std::string &result,
            ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/cluster/all";

    // send request
    return request->sendGetRequest(result, path, "", error);
}

/**
 * @brief delete a cluster with all its tasks from kyouko
 *
 * @param result reference for response-message
 * @param clusterUuid uuid of the cluster to delete
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
deleteCluster(std::string &result,
              const std::string &clusterUuid,
              ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/cluster";
    const std::string vars = "uuid=" + clusterUuid;

    // send request
    return request->sendDeleteRequest(result, path, vars, error);
}

/**
 * @brief create a snapshot of a cluster
 *
 * @param result reference for response-message
 * @param clusterUuid uuid of the cluster to delete
 * @param snapshotName name of the new snapshot
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
saveCluster(std::string &result,
            const std::string &clusterUuid,
            const std::string &snapshotName,
            ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/cluster/save";
    const std::string vars = "";
    const std::string jsonBody = "{\"name\":\""
                                 + snapshotName
                                 + "\",\"cluster_uuid\":\""
                                 + clusterUuid
                                 + "\"}";

    // send request
    return request->sendPostRequest(result, path, vars, jsonBody, error);
}

/**
 * @brief restore cluster from a snapshot
 *
 * @param result reference for response-message
 * @param clusterUuid uuid of the cluster to delete
 * @param snapshotUuid uuid of the snapshot, which should be loaded into the cluster
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
restoreCluster(std::string &result,
               const std::string &clusterUuid,
               const std::string &snapshotUuid,
               ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/cluster/load";
    const std::string vars = "";
    const std::string jsonBody = "{\"snapshot_uuid\":\""
                                 + snapshotUuid
                                 + "\",\"cluster_uuid\":\""
                                 + clusterUuid
                                 + "\"}";

    // send request
    return request->sendPostRequest(result, path, vars, jsonBody, error);
}

/**
 * @brief switchToTaskMode
 * @param result
 * @param clusterUuid
 * @param error
 * @return
 */
bool
switchToTaskMode(std::string &result,
                 const std::string &clusterUuid,
                 ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/cluster/set_mode";
    const std::string vars = "";
    const std::string jsonBody = "{\"new_state\":\"TASK\""
                                 ",\"uuid\":\""
                                 + clusterUuid
                                 + "\"}";

    // send request
    return request->sendPutRequest(result, path, vars, jsonBody, error);
}

/**
 * @brief switchToDirectMode
 * @param result
 * @param clusterUuid
 * @param error
 * @return
 */
WebsocketClient*
switchToDirectMode(std::string &result,
                   const std::string &clusterUuid,
                   ErrorContainer &error)
{
    WebsocketClient* wsClient = new WebsocketClient();
    std::string websocketUuid = "";
    const bool ret = wsClient->initClient(websocketUuid,
                                          HanamiRequest::getInstance()->getToken(),
                                          "kyouko",
                                          HanamiRequest::getInstance()->getHost(),
                                          HanamiRequest::getInstance()->getPort(),
                                          error);
    if(ret == false)
    {
        error.addMeesage("Failed to init websocket to kyouko");
        LOG_ERROR(error);
        delete wsClient;
        return nullptr;
    }

    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/cluster/set_mode";
    const std::string vars = "";
    const std::string jsonBody = "{\"connection_uuid\":\""
                                 + websocketUuid
                                 + "\",\"new_state\":\"DIRECT\""
                                   ",\"uuid\":\""
                                 + clusterUuid
                                 + "\"}";

    // send request
    if(request->sendPutRequest(result, path, vars, jsonBody, error) == false)
    {
        delete wsClient;
        return nullptr;
    }

    return wsClient;
}

} // namespace Hanami
} // namespace Kitsunemimi
