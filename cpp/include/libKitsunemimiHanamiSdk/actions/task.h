#ifndef TASK_H
#define TASK_H

#include <libKitsunemimiCommon/logger.h>
#include <libKitsunemimiHanamiSdk/common/hanami_request.h>

namespace Kitsunemimi
{
namespace Hanami
{

bool createLearnTask(std::string &result,
                     const std::string &clusterUuid,
                     const std::string &inputs,
                     const std::string &labels,
                     const std::string &type,
                     ErrorContainer &error);

bool createRequestTask(std::string &result,
                       const std::string &clusterUuid,
                       const std::string &inputs,
                       const std::string &type,
                       ErrorContainer &error);

bool getTask(std::string &result,
             const std::string &taskUuid,
             const std::string &clusterUuid,
             ErrorContainer &error);

bool listTask(std::string &result,
              ErrorContainer &error);

bool deleteTask(std::string &result,
                const std::string &taskUuid,
                ErrorContainer &error);

}
}

#endif // TASK_H
