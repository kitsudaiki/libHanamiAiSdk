#include <libKitsunemimiHanamiSdk/actions/cluster.h>

namespace Kitsunemimi
{
namespace Hanami
{

bool
createLearnTask(std::string &result,
                const std::string &clusterUuid,
                const std::string &inputs,
                const std::string &labels,
                const std::string &type,
                ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/task/learn";
    const std::string vars = "";
    const std::string jsonBody = "{\"cluster_uuid\":\""
                                 + clusterUuid
                                 + "\",\"inputs\":\""
                                 + inputs
                                 + "\",\"labels\":\""
                                 + labels
                                 + "\",\"type\":\""
                                 + type
                                 + "\"}";

    return request->sendPostRequest(result, path, vars, jsonBody, error);
}

bool
createRequestTask(std::string &result,
                  const std::string &clusterUuid,
                  const std::string &inputs,
                  const std::string &type,
                  ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/task/request";
    const std::string vars = "";
    const std::string jsonBody = "{\"cluster_uuid\":\""
                                 + clusterUuid
                                 + "\",\"inputs\":\""
                                 + inputs
                                 + "\",\"type\":\""
                                 + type
                                 + "\"}";

    return request->sendPostRequest(result, path, vars, jsonBody, error);
}

bool
getTask(std::string &result,
        const std::string &taskUuid,
        const std::string &clusterUuid,
        ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/task";
    const std::string vars = "uuid=" + taskUuid + "&cluster_uuid=" + clusterUuid;

    return request->sendGetRequest(result, path, vars, error);
}

bool
listTask(std::string &result,
         ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/task/all";

    return request->sendGetRequest(result, path, "", error);
}

bool
deleteTask(std::string &result,
           const std::string &taskUuid,
           ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/task";
    const std::string vars = "uuid=" + taskUuid;

    return request->sendDeleteRequest(result, path, vars, error);
}

}
}
