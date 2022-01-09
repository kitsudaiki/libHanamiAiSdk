#ifndef CLUSTER_H
#define CLUSTER_H

#include <libKitsunemimiCommon/logger.h>
#include <libKitsunemimiHanamiSdk/common/hanami_request.h>

namespace Kitsunemimi
{
namespace Hanami
{

bool createCluster(std::string &result,
                   const std::string &clusterName,
                   const std::string &templateUuid,
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
