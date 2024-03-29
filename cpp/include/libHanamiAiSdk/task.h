/**
 * @file        task.h
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

#ifndef KITSUNEMIMI_HANAMISDK_TASK_H
#define KITSUNEMIMI_HANAMISDK_TASK_H

#include <libKitsunemimiCommon/logger.h>

namespace HanamiAI
{

bool createTask(std::string &result,
                const std::string &name,
                const std::string &type,
                const std::string &clusterUuid,
                const std::string &dataSetUuid,
                Kitsunemimi::ErrorContainer &error);

bool getTask(std::string &result,
             const std::string &taskUuid,
             const std::string &clusterUuid,
             Kitsunemimi::ErrorContainer &error);

bool listTask(std::string &result,
              const std::string &clusterUuid,
              Kitsunemimi::ErrorContainer &error);

bool deleteTask(std::string &result,
                const std::string &taskUuid,
                const std::string &clusterUuid,
                Kitsunemimi::ErrorContainer &error);

} // namespace HanamiAI

#endif // KITSUNEMIMI_HANAMISDK_TASK_H
