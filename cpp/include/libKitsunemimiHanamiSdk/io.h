#ifndef IO_H
#define IO_H

#include <string>
#include <stdint.h>

bool learn(const std::string &clusterUuid,
           const float* inputData,
           const uint64_t numberOfInputValues,
           const float* shouldOutputData,
           const uint64_t numberOfOutputalues);

float* request(const std::string &clusterUuid,
               const float* inputData,
               const uint64_t numberOfInputValues,
               uint64_t &numberOfOutputValues);

#endif // IO_H
