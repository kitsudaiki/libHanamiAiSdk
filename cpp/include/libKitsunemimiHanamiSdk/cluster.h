/**
 * @file        cluster.h
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

#ifndef KITSUNEMIMI_HANAMISDK_CLUSTER_H
#define KITSUNEMIMI_HANAMISDK_CLUSTER_H

#include <libKitsunemimiCommon/logger.h>

namespace Kitsunemimi
{
namespace Hanami
{

bool createCluster(std::string &result,
                   const std::string &clusterName,
                   const std::string &templateUuid,
                   ErrorContainer &error);

bool getCluster(std::string &result,
                const std::string &clusterUuid,
                ErrorContainer &error);

bool listCluster(std::string &result,
                 ErrorContainer &error);

bool deleteCluster(std::string &result,
                   const std::string &clusterUuid,
                   ErrorContainer &error);

bool saveCluster(std::string &result,
                 const std::string &clusterUuid,
                 const std::string &snapshotName,
                 ErrorContainer &error);

bool restoreCluster(std::string &result,
                    const std::string &clusterUuid,
                    const std::string &snapshotUuid,
                    ErrorContainer &error);

} // namespace Hanami
} // namespace Kitsunemimi

#endif // KITSUNEMIMI_HANAMISDK_CLUSTER_H
