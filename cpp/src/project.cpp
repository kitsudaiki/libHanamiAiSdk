/**
 * @file        project.cpp
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

#include <libKitsumiAiSdk/project.h>
#include <common/http_client.h>

namespace Kitsunemimi
{
namespace Hanami
{

/**
 * @brief create a new user in misaki
 *
 * @param result reference for response-message
 * @param projectName name of the new project
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
createProject(std::string &result,
           const std::string &projectName,
           ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/misaki/v1/project";
    const std::string vars = "";
    const std::string jsonBody = "{\"name\":\""
                                 + projectName
                                 + "\"}";

    // send request
    if(request->sendPostRequest(result, path, vars, jsonBody, error) == false)
    {
        error.addMeesage("Failed to create project with name '" + projectName + "'");
        LOG_ERROR(error);
        return false;
    }

    return true;
}

/**
 * @brief get information of a user from misaki
 *
 * @param result reference for response-message
 * @param projectName name of the requested project
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
getProject(std::string &result,
           const std::string &projectName,
           ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/misaki/v1/project";
    const std::string vars = "name=" + projectName;

    if(request->sendGetRequest(result, path, vars, error) == false)
    {
        error.addMeesage("Failed to get project with name '" + projectName + "'");
        LOG_ERROR(error);
        return false;
    }

    return true;
}

/**
 * @brief list all visible users on misaki
 *
 * @param result reference for response-message
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
listProject(std::string &result,
           ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/misaki/v1/project/all";

    // send request
    if(request->sendGetRequest(result, path, "", error) == false)
    {
        error.addMeesage("Failed to list projects");
        LOG_ERROR(error);
        return false;
    }

    return true;
}

/**
 * @brief delete a project from misaki
 *
 * @param result reference for response-message
 * @param projectName name of the project, which should be deleted
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
deleteProject(std::string &result,
              const std::string &projectName,
              ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/misaki/v1/project";
    const std::string vars = "name=" + projectName;

    // send request
    if(request->sendDeleteRequest(result, path, vars, error) == false)
    {
        error.addMeesage("Failed to delete project with name '" + projectName + "'");
        LOG_ERROR(error);
        return false;
    }

    return true;
}

} // namespace Hanami
} // namespace Kitsunemimi
