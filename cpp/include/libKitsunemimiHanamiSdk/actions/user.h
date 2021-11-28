#ifndef USER_H
#define USER_H

#include <libKitsunemimiCommon/logger.h>
#include <libKitsunemimiHanamiSdk/common/hanami_request.h>

namespace Kitsunemimi
{
namespace Hanami
{

bool listUser(std::string &result,
              HanamiRequest &request,
              ErrorContainer &error);

}
}

#endif // USER_H
