#include <libKitsunemimiHanamiSdk/actions/user.h>

namespace Kitsunemimi
{
namespace Hanami
{

/**
 * @brief createUser
 * @param result
 * @param userName
 * @param password
 * @param isAdmin
 * @param roles
 * @param projects
 * @param error
 * @return
 */
bool
createUser(std::string &result,
           const std::string &userName,
           const std::string &password,
           const bool isAdmin,
           const std::string &roles,
           const std::string &projects,
           ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/misaka/user";
    const std::string vars = "";
    const std::string jsonBody = "{\"user_name\":\""
                                 + userName
                                 + "\",\"pw\":\""
                                 + password
                                 + "\",\"is_admin\":"
                                 + (isAdmin ? "true" : "false") +
                                 + ",\"user_roles\":\""
                                 + roles
                                 + "\",\"user_projects\":\""
                                 + projects
                                 + "\"}";

    return request->sendPostRequest(result, path, vars, jsonBody, error);
}

/**
 * @brief getUser
 * @param result
 * @param userName
 * @param error
 * @return
 */
bool
getUser(std::string &result,
        const std::string &userName,
        ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/misaka/user";
    const std::string vars = "user_name=" + userName;

    return request->sendGetRequest(result, path, vars, error);
}

/**
 * @brief listUser
 * @param result
 * @param error
 * @return
 */
bool
listUser(std::string &result,
         ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/misaka/user/all";

    return request->sendGetRequest(result, path, "", error);
}

/**
 * @brief deleteUser
 * @param result
 * @param userName
 * @param error
 * @return
 */
bool
deleteUser(std::string &result,
           const std::string &userName,
           ErrorContainer &error)
{
    HanamiRequest* request = HanamiRequest::getInstance();
    const std::string path = "/control/misaka/user";
    const std::string vars = "user_name=" + userName;

    return request->sendDeleteRequest(result, path, vars, error);
}

}
}
