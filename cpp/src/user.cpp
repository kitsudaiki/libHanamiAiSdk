/**
 * @file        user.cpp
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

#include <libKitsunemimiHanamiSdk/user.h>
#include <common/http_client.h>

namespace Kitsunemimi
{
namespace Hanami
{

/**
 * @brief create a new user in misaka
 *
 * @param result reference for response-message
 * @param userName name of the new user
 * @param password password of the new user
 * @param isAdmin true to make new user to an admin
 * @param roles name of role of the user
 * @param projects uuid of the project of the new user
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
createUser(std::string &result,
           const std::string &userName,
           const std::string &password,
           const bool isAdmin,
           const std::string &roles,
           const std::string &projects,
           ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/misaka/v1/user";
    const std::string vars = "";
    const std::string jsonBody = "{\"name\":\""
                                 + userName
                                 + "\",\"pw\":\""
                                 + password
                                 + "\",\"is_admin\":"
                                 + (isAdmin ? "true" : "false") +
                                 + ",\"roles\":\""
                                 + roles
                                 + "\",\"projects\":\""
                                 + projects
                                 + "\"}";

    // send request
    if(request->sendPostRequest(result, path, vars, jsonBody, error) == false)
    {
        error.addMeesage("Failed to create user with name '" + userName + "'");
        LOG_ERROR(error);
        return false;
    }

    return true;
}

/**
 * @brief get information of a user from misaka
 *
 * @param result reference for response-message
 * @param userName name of the requested user
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
getUser(std::string &result,
        const std::string &userName,
        ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/misaka/v1/user";
    const std::string vars = "name=" + userName;

    if(request->sendGetRequest(result, path, vars, error) == false)
    {
        error.addMeesage("Failed to get user with name '" + userName + "'");
        LOG_ERROR(error);
        return false;
    }

    return true;
}

/**
 * @brief list all visible users on misaka
 *
 * @param result reference for response-message
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
listUser(std::string &result,
         ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/misaka/v1/user/all";

    // send request
    if(request->sendGetRequest(result, path, "", error) == false)
    {
        error.addMeesage("Failed to list users");
        LOG_ERROR(error);
        return false;
    }

    return true;
}

/**
 * @brief delete a user from misaka
 *
 * @param result reference for response-message
 * @param userName name of the user, which should be deleted
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
deleteUser(std::string &result,
           const std::string &userName,
           ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/misaka/v1/user";
    const std::string vars = "name=" + userName;

    // send request
    if(request->sendDeleteRequest(result, path, vars, error) == false)
    {
        error.addMeesage("Failed to delete user with name '" + userName + "'");
        LOG_ERROR(error);
        return false;
    }

    return true;
}

} // namespace Hanami
} // namespace Kitsunemimi
