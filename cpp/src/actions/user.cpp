#include <libKitsunemimiHanamiSdk/actions/user.h>

namespace Kitsunemimi
{
namespace Hanami
{

bool
listUser(std::string &result,
         HanamiRequest &request,
         ErrorContainer &error)
{
    const std::string path = "/control/misaka/users";
    return request.sendGetRequest(result, path, "", error);
}

}
}
