/**
 * @file        data_set.h
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

#ifndef KITSUNEMIMI_HANAMISDK_DATA_SET_H
#define KITSUNEMIMI_HANAMISDK_DATA_SET_H

#include <libKitsunemimiCommon/logger.h>
#include <libKitsunemimiHanamiSdk/common/http_client.h>

namespace Kitsunemimi
{
namespace Hanami
{

bool uploadCsvData(std::string &result,
                   const std::string &dataSetName,
                   const std::string &inputFilePath,
                   ErrorContainer &error);

bool uploadMnistData(std::string &result,
                     const std::string &dataSetName,
                     const std::string &inputFilePath,
                     const std::string &labelFilePath,
                     ErrorContainer &error);

bool checkDataset(std::string &result,
                  const std::string &dataUuid,
                  const std::string &resultUuid,
                  ErrorContainer &error);

bool getDataset(std::string &result,
                const std::string &dataUuid,
                ErrorContainer &error);

bool listDatasets(std::string &result,
                  ErrorContainer &error);

bool deleteDataset(std::string &result,
                   const std::string &dataUuid,
                   ErrorContainer &error);

bool getDatasetProgress(std::string &result,
                   const std::string &dataUuid,
                   ErrorContainer &error);

} // namespace Hanami
} // namespace Kitsunemimi

#endif // KITSUNEMIMI_HANAMISDK_DATA_SET_H
