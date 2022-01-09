#include <libKitsunemimiHanamiSdk/actions/template.h>

namespace Kitsunemimi
{
namespace Hanami
{

bool
createTemplate(std::string &result,
               const std::string &templateName,
               const uint32_t numberOfInputs,
               const uint32_t numberOfOutputs,
               ErrorContainer &error)
{
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

    return request->sendPostRequest(result, path, vars, jsonBody, error);
}

bool
getTemplate(std::string &result,
            const std::string &templateName,
            ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/template";
    const std::string vars = "name=" + templateName;

    return request->sendGetRequest(result, path, vars, error);
}

bool
listTemplate(std::string &result,
             ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/template/all";

    return request->sendGetRequest(result, path, "", error);
}

bool
deleteTemplate(std::string &result,
               const std::string &templateName,
               ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/template";
    const std::string vars = "name=" + templateName;

    return request->sendDeleteRequest(result, path, vars, error);
}

}
}
