/**
 * @file        template.cpp
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

#include <libKitsunemimiHanamiSdk/template.h>
#include <common/http_client.h>

namespace Kitsunemimi
{
namespace Hanami
{

/**
 * @brief generate a new template on kyouko
 *
 * @param result reference for response-message
 * @param templateName name of the new template
 * @param dataSetUuid uuid of the data-set, which should work as base to get init-information
 * @param type to the template to create
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
generateTemplate(std::string &result,
                 const std::string &templateName,
                 const std::string &dataSetUuid,
                 const std::string &type,
                 ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/template";
    const std::string vars = "";
    const std::string jsonBody = "{\"name\":\""          + templateName + "\","
                                 " \"type\":\""          + type + "\","
                                 " \"data_set_uuid\":\"" + dataSetUuid  + "\"}";

    // send request
    return request->sendPostRequest(result, path, vars, jsonBody, error);
}

/**
 * @brief get a specific template from kyouko
 *
 * @param result reference for response-message
 * @param templateUuid uuid of the template to get
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
getTemplate(std::string &result,
            const std::string &templateUuid,
            ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/template";
    const std::string vars = "uuid=" + templateUuid;

    // send request
    return request->sendGetRequest(result, path, vars, error);
}

/**
 * @brief list all visible templates on kyouko
 *
 * @param result reference for response-message
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
listTemplate(std::string &result,
             ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/template/all";

    // send request
    return request->sendGetRequest(result, path, "", error);
}

/**
 * @brief delete a template form kyouko
 *
 * @param result reference for response-message
 * @param templateUuid uuid of the template to delete
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
deleteTemplate(std::string &result,
               const std::string &templateUuid,
               ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/template";
    const std::string vars = "uuid=" + templateUuid;

    // send request
    return request->sendDeleteRequest(result, path, vars, error);
}

} // namespace Hanami
} // namespace Kitsunemimi
