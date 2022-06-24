#include <libKitsunemimiHanamiSdk/io.h>

/**
 * @brief learn
 * @param clusterUuid
 * @param inputData
 * @param numberOfInputValues
 * @param shouldOutputData
 * @param numberOfOutputalues
 * @return
 */
bool
learn(const std::string &clusterUuid,
      const float* inputData,
      const uint64_t numberOfInputValues,
      const float* shouldOutputData,
      const uint64_t numberOfOutputalues)
{

}

/**
 * @brief request
 * @param clusterUuid
 * @param inputData
 * @param numberOfInputValues
 * @param numberOfOutputValues
 * @return
 */
float*
request(const std::string &clusterUuid,
        const float* inputData,
        const uint64_t numberOfInputValues,
        uint64_t &numberOfOutputValues)
{

}
