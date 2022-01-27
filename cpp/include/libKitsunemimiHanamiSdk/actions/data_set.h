#ifndef DATA_SET_H
#define DATA_SET_H

#include <libKitsunemimiCommon/logger.h>
#include <libKitsunemimiHanamiSdk/common/hanami_request.h>

namespace Kitsunemimi
{
namespace Hanami
{

bool uploadMnistData(std::string &result,
                     const std::string &dataSetName,
                     const std::string &inputFilePath,
                     const std::string &labelFilePath,
                     ErrorContainer &error);

bool getDataset(std::string &result,
                const std::string &dataUuid,
                ErrorContainer &error);

bool listDatasets(std::string &result,
                  ErrorContainer &error);

bool deleteDataset(std::string &result,
                   const std::string &dataUuid,
                   ErrorContainer &error);

} // namespace Hanami
} // namespace Kitsunemimi

#endif // DATA_SET_H
