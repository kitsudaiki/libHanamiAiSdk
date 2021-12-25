#include <libKitsunemimiHanamiSdk/actions/cluster.h>

namespace Kitsunemimi
{
namespace Hanami
{

bool
createClusterGenerate(std::string &result,
                      const std::string &clusterName,
                      const uint32_t numberOfInputs,
                      const uint32_t numberOfOutputs,
                      ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/cluster/generate";
    const std::string vars = "";
    const std::string jsonBody = "{\"cluster_name\":\""
                                 + clusterName
                                 + "\",\"number_of_inputs\":"
                                 + std::to_string(numberOfInputs)
                                 + ",\"number_of_outputs\":"
                                 + std::to_string(numberOfOutputs)
                                 + "}";

    return request->sendPostRequest(result, path, vars, jsonBody, error);
}

bool
getCluster(std::string &result,
           const std::string &clusterName,
           ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/cluster";
    const std::string vars = "cluster_name=" + clusterName;

    return request->sendGetRequest(result, path, vars, error);
}

bool
listCluster(std::string &result,
            ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/cluster/all";

    return request->sendGetRequest(result, path, "", error);
}

bool
deleteCluster(std::string &result,
              const std::string &clusterName,
              ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/kyouko/v1/cluster";
    const std::string vars = "cluster_name=" + clusterName;

    return request->sendDeleteRequest(result, path, vars, error);
}

}
}
