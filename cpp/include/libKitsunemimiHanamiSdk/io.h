#ifndef IO_H
#define IO_H

#include <string>
#include <stdint.h>

#include <libKitsunemimiCommon/logger.h>

namespace Kitsunemimi
{
namespace Hanami
{
class WebsocketClient;

bool learn(Kitsunemimi::Hanami::WebsocketClient* wsClient,
           float* inputValues,
           const uint64_t numberOfInputValues,
           float* shouldValues,
           const uint64_t numberOfShouldValues,
           Kitsunemimi::ErrorContainer &error);

float* request(Kitsunemimi::Hanami::WebsocketClient* wsClient,
               float* inputData,
               const uint64_t numberOfInputValues,
               uint64_t &numberOfOutputValues,
               Kitsunemimi::ErrorContainer &error);

} // namespace Hanami
} // namespace Kitsunemimi

#endif // IO_H
