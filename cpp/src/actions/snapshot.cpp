/**
 * @file        snapshot.cpp
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

#include <libKitsunemimiHanamiSdk/actions/snapshot.h>

namespace Kitsunemimi
{
namespace Hanami
{

/**
 * @brief get information of a snapshot from sagiri
 *
 * @param result reference for response-message
 * @param snapshotUuid uuid of the snapshot to get
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
getSnapshot(std::string &result,
            const std::string &snapshotUuid,
            ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/sagiri/v1/cluster_snapshot";
    const std::string vars = "uuid=" + snapshotUuid;

    // send request
    return request->sendGetRequest(result, path, vars, error);
}

/**
 * @brief list all visible snapshot on sagiri
 *
 * @param result reference for response-message
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
listSnapshot(std::string &result,
             ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/sagiri/v1/cluster_snapshot/all";

    // send request
    return request->sendGetRequest(result, path, "", error);
}

/**
 * @brief delete a snapshot
 *
 * @param result reference for response-message
 * @param snapshotUuid uuid of the snapshot to delete
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
deleteSnapshot(std::string &result,
               const std::string &snapshotUuid,
               ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/sagiri/v1/cluster_snapshot";
    const std::string vars = "uuid=" + snapshotUuid;

    // send request
    return request->sendDeleteRequest(result, path, vars, error);
}

} // namespace Hanami
} // namespace Kitsunemimi
