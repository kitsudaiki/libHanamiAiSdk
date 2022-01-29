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

#include <libKitsunemimiHanamiSdk/actions/template.h>

namespace Kitsunemimi
{
namespace Hanami
{

/**
 * @brief generate a new template on kyouko
 *
 * @param result reference for response-message
 * @param templateName name of the new template
 * @param numberOfInputs number of inputs for the template
 * @param numberOfOutputs number of outputs for the template
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
createTemplate(std::string &result,
               const std::string &templateName,
               const uint32_t numberOfInputs,
               const uint32_t numberOfOutputs,
               ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/template";
    const std::string vars = "";
    const std::string jsonBody = "{\"name\":\""
                                 + templateName
                                 + "\",\"number_of_inputs\":"
                                 + std::to_string(numberOfInputs)
                                 + ",\"number_of_outputs\":"
                                 + std::to_string(numberOfOutputs)
                                 + "}";

    // send request
    return request->sendPostRequest(result, path, vars, jsonBody, error);
}

/**
 * @brief get a specific template from kyouko
 *
 * @param result reference for response-message
 * @param templateName name of the requested template
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
getTemplate(std::string &result,
            const std::string &templateName,
            ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/template";
    const std::string vars = "name=" + templateName;

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
 * @param templateName name of the template to dele
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
deleteTemplate(std::string &result,
               const std::string &templateName,
               ErrorContainer &error)
{
    // create request
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/template";
    const std::string vars = "name=" + templateName;

    // send request
    return request->sendDeleteRequest(result, path, vars, error);
}

} // namespace Hanami
} // namespace Kitsunemimi
