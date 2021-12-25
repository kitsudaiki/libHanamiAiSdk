#ifndef CLUSTER_H
#define CLUSTER_H

#include <libKitsunemimiCommon/logger.h>
#include <libKitsunemimiHanamiSdk/common/hanami_request.h>

namespace Kitsunemimi
{
namespace Hanami
{

bool createClusterGenerate(std::string &result,
                           const std::string &clusterName,
                           const uint32_t numberOfInputs,
                           const uint32_t numberOfOutputs,
                           ErrorContainer &error);

bool getCluster(std::string &result,
                const std::string &clusterName,
                ErrorContainer &error);

bool listCluster(std::string &result,
                 ErrorContainer &error);

bool deleteCluster(std::string &result,
                   const std::string &clusterName,
                   ErrorContainer &error);

}
}

#endif // CLUSTER_H
