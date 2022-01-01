#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <libKitsunemimiCommon/logger.h>
#include <libKitsunemimiHanamiSdk/common/hanami_request.h>

namespace Kitsunemimi
{
namespace Hanami
{

bool createTemplate(std::string &result,
                    const std::string &templateName,
                    const uint32_t numberOfInputs,
                    const uint32_t numberOfOutputs,
                    ErrorContainer &error);

bool getTemplate(std::string &result,
                 const std::string &templateName,
                 ErrorContainer &error);

bool listTemplate(std::string &result,
                  ErrorContainer &error);

bool deleteTemplate(std::string &result,
                    const std::string &templateName,
                    ErrorContainer &error);

}
}

#endif // TEMPLATE_H
