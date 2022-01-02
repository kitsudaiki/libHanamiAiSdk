#ifndef CLUSTER_H
#define CLUSTER_H

#include <libKitsunemimiCommon/logger.h>
#include <libKitsunemimiHanamiSdk/common/hanami_request.h>

namespace Kitsunemimi
{
namespace Hanami
{

bool uploadTrainData(std::string &result,
                     const std::string &dataName,
                     const std::string &dataType,
                     const std::string &localFilePath,
                     ErrorContainer &error);

bool getTrainData(std::string &result,
                  const std::string &dataUuid,
                  ErrorContainer &error);

bool listTrainData(std::string &result,
                   ErrorContainer &error);

bool deleteTrainData(std::string &result,
                     const std::string &dataUuid,
                     ErrorContainer &error);

}
}

#endif // CLUSTER_H
