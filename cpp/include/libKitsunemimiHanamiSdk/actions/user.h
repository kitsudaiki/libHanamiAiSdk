#ifndef USER_H
#define USER_H

#include <libKitsunemimiCommon/logger.h>
#include <libKitsunemimiHanamiSdk/common/hanami_request.h>

namespace Kitsunemimi
{
namespace Hanami
{

bool createUser(std::string &result,
                const std::string &userName,
                const std::string &password,
                const bool isAdmin,
                const std::string &roles,
                const std::string &projects,
                ErrorContainer &error);

bool getUser(std::string &result,
             const std::string &userName,
             ErrorContainer &error);

bool listUser(std::string &result,
              ErrorContainer &error);

bool deleteUser(std::string &result,
                const std::string &userName,
                ErrorContainer &error);

}
}

#endif // USER_H
