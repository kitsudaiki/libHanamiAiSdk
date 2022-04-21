/**
 * @file        request.cpp
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

#include <libKitsunemimiHanamiSdk/common/http_client.h>

#include <libKitsunemimiSakuraNetwork/session_controller.h>
#include <libKitsunemimiSakuraNetwork/session.h>

#include <libKitsunemimiHanamiCommon/uuid.h>

#include <libKitsunemimiJson/json_item.h>

namespace Kitsunemimi
{
namespace Hanami
{
/**
 * @brief errorCallback
 */
void errorCallback(Kitsunemimi::Sakura::Session*,
                   const uint8_t,
                   const std::string message)
{
    std::cout<<"ERROR: "<<message<<std::endl;
}

// empty callbacks
void sessionCreateCallback(Kitsunemimi::Sakura::Session*, const std::string) {}
void sessionCloseCallback(Kitsunemimi::Sakura::Session*, const std::string) {}

Kitsunemimi::Hanami::HanamiRequest* HanamiRequest::m_instance = nullptr;

/**
 * @brief constructor
 */
HanamiRequest::HanamiRequest() {}

const std::string&
HanamiRequest::getHost() const
{
    return m_host;
}

const std::string&
HanamiRequest::getPort() const
{
    return m_port;
}

/**
 * @brief HanamiRequest::token
 * @return
 */
const std::string&
HanamiRequest::getToken() const
{
    return m_token;
}

/**
 * @brief static methode to get instance of the interface
 *
 * @return pointer to the static instance
 */
HanamiRequest*
HanamiRequest::getInstance()
{
    if(m_instance == nullptr) {
        m_instance = new HanamiRequest();
    }

    return m_instance;
}

/**
 * @brief destructor
 */
HanamiRequest::~HanamiRequest()
{
    if(m_sessionController != nullptr) {
        delete m_sessionController;
    }
}

/**
 * @brief init request-object
 *
 * @param host target-host-address
 * @param port port of the server
 * @param user user-name for token-request
 * @param pw pw for token-request
 * @param cacert cacert for connection-validation
 *
 * @return false, if host or port ar missing in variables and venv, else true
 */
bool
HanamiRequest::init(const std::string &host,
                    const std::string &port,
                    const std::string &user,
                    const std::string &pw,
                    const std::string &cacert)
{
    m_host = host;
    m_port = port;
    m_cacert = cacert;
    m_user = user;
    m_pw = pw;

    // get host-address
    if(m_host == ""
        && getEnvVar(m_host, "HANAMI_ADDRESS") == false)
    {
        return false;
    }

    // get target-port
    if(m_port == ""
        && getEnvVar(m_port, "HANAMI_PORT") == false)
    {
        return false;
    }

    // ge ca-cert
    if(m_cacert == "") {
        getEnvVar(m_cacert, "HANAMI_CACERT");
    }

    // get token if there already one exist
    getEnvVar(m_token, "HANAMI_TOKEN");

    return true;
}

/**
 * @brief create a sakura-session to a specific component on server-side
 *
 * @param target name of the target-component on server-side
 * @param error reference for error-output
 *
 * @return pointer to session, which forwards to the requested component if successful, else nullptr
 */
Sakura::Session*
HanamiRequest::createSakuraSession(const std::string &target,
                                   Kitsunemimi::ErrorContainer &error)
{
    // init new session-container-isntance if not already done
    if(m_sessionController == nullptr)
    {
        m_sessionController = new Sakura::SessionController(&sessionCreateCallback,
                                                            &sessionCloseCallback,
                                                            &errorCallback);
    }

    const std::string sessionId = generateUuid().toString();

    // create tls-connection to the torii
    const int port = std::stoi(m_port);
    Sakura::Session* session = m_sessionController->startTcpSession(m_host,
                                                                    port + 1,
                                                                    sessionId,
                                                                    sessionId,
                                                                    error);

    if(session == nullptr) {
        return nullptr;
    }

    // build request to forward session
    const std::string path = "/control/torii/v1/forward_session";
    const std::string vars = "";
    const std::string jsonBody = "{\"source_name\":\"" + sessionId
                                 + "\",\"target_name\":\"" + target
                                 + "\"}";

    // send request to forward session
    std::string result;
    if(sendPostRequest(result, path, vars, jsonBody, error) == false)
    {
        session->closeSession(error);
        return nullptr;
    }

    return session;
}

/**
 * @brief Request::sendGetRequest
 *
 * @param response reference for response-output
 * @param path path to call
 * @param vars variables as string for the request-path
 * @param error reference for error-output
 *
 * @return false, if something went wrong while sending or token-request failed, else true
 */
bool
HanamiRequest::sendGetRequest(std::string &response,
                              const std::string &path,
                              const std::string &vars,
                              ErrorContainer &error)
{
    return makeRequest(response, http::verb::get, path, vars, "", error);
}

/**
 * @brief Request::sendPostRequest
 *
 * @param response reference for response-output
 * @param path path to call
 * @param vars variables as string for the request-path
 * @param body json-body as string
 * @param error reference for error-output
 *
 * @return false, if something went wrong while sending or token-request failed, else true
 */
bool
HanamiRequest::sendPostRequest(std::string &response,
                               const std::string &path,
                               const std::string &vars,
                               const std::string &body,
                               ErrorContainer &error)
{
    return makeRequest(response, http::verb::post, path, vars, body, error);
}

/**
 * @brief Request::sendPutRequest
 *
 * @param response reference for response-output
 * @param path path to call
 * @param vars variables as string for the request-path
 * @param body json-body as string
 * @param error reference for error-output
 *
 * @return false, if something went wrong while sending or token-request failed, else true
 */
bool
HanamiRequest::sendPutRequest(std::string &response,
                              const std::string &path,
                              const std::string &vars,
                              const std::string &body,
                              ErrorContainer &error)
{
    return makeRequest(response, http::verb::put, path, vars, body, error);
}

/**
 * @brief Request::sendDeleteRequest
 *
 * @param response reference for response-output
 * @param path path to call
 * @param vars variables as string for the request-path
 * @param error reference for error-output
 *
 * @return false, if something went wrong while sending or token-request failed, else true
 */
bool
HanamiRequest::sendDeleteRequest(std::string &response,
                                 const std::string &path,
                                 const std::string &vars,
                                 ErrorContainer &error)
{
    return makeRequest(response, http::verb::delete_, path, vars, "", error);
}

/**
 * @brief get content of an environment-variable
 *
 * @param content reference for output
 * @param key name of the environment-variable
 *
 * @return false, if varibale is not set, else true
 */
bool
HanamiRequest::getEnvVar(std::string &content,
                   const std::string &key) const
{
    char* val = getenv(key.c_str());
    if(val == NULL) {
        return false;
    }

    content = std::string(val);
    return true;
}

/**
 * @brief Request::requestToken
 *
 * @param error reference for error-output
 *
 * @return false, if something failed, else true
 */
bool
HanamiRequest::requestToken(ErrorContainer &error)
{
    // get user for access
    if(m_user == ""
        && getEnvVar(m_user, "HANAMI_USER") == false)
    {
        return false;
    }

    // get password for access
    if(m_pw == ""
        && getEnvVar(m_pw, "HANAMI_PW") == false)
    {
        return false;
    }

    // build request-path
    std::string path = "/control/misaka/v1/token?name=";
    path.append(m_user);
    path.append("&pw=");
    path.append(m_pw);

    // make token-request
    std::string response;
    if(makeSingleRequest(response, http::verb::get, path, "", error) != 200)
    {
        error.addMeesage("failed to request token");
        return false;
    }

    // try to parse response
    Kitsunemimi::Json::JsonItem item;
    if(item.parse(response, error) == false)
    {
        error.addMeesage("failed to parse token-response");
        return false;
    }

    // get token from parsed item
    m_token = item["token"].getString();
    if(m_token == "")
    {
        error.addMeesage("can not find token in token-response");
        return false;
    }

    return true;
}

/**
 * @brief make a request against the backend
 *
 * @param response reference for response-output
 * @param type request-type
 * @param path path to call
 * @param vars variables as string for the request-path
 * @param jsonBody json-body as string
 * @param error reference for error-output
 *
 * @return false, if something went wrong while sending or token-request failed, else true
 */
bool
HanamiRequest::makeRequest(std::string &response,
                           const http::verb type,
                           const std::string &path,
                           const std::string &vars,
                           const std::string &jsonBody,
                           ErrorContainer &error)
    {
    // get token if necessary
    if(m_token == "")
    {
        if(requestToken(error) == false) {
            return false;
        }
    }

    // build real request-path with the ntoken
    std::string target = path;
    if(vars != "") {
        target.append("?" + vars);
    }

    // send request
    if(makeSingleRequest(response, type, target, jsonBody, error) != 200) {
        return false;
    }

    // handle expired token
    if(response == "Token is expired")
    {
        // request new token
        if(requestToken(error) == false) {
            return false;
        }

        // build new request-path with the new token
        target = path;
        if(m_token != "") {
            target += "?token=" + m_token;
        }
        if(vars != "") {
            target.append("&" + vars);
        }

        // try request again
        if(makeSingleRequest(response, type, target, jsonBody, error) != 200) {
            return false;
        }
    }

    return true;
}

/**
 * @brief make a generic request against the backend
 *
 * @param response reference for response-output
 * @param type type of the request
 * @param target target-path as string
 * @param jsonBody json-body as string
 * @param error reference for error-output
 *
 * @return false, if something went wrong while sending, else true
 */
uint16_t
HanamiRequest::makeSingleRequest(std::string &response,
                                 const http::verb type,
                                 const std::string &target,
                                 const std::string &jsonBody,
                                 ErrorContainer &error)
{
    u_int16_t statusCode = 0;

    try
    {
        int version = 11;

        // init ssl
        ssl::context ctx(ssl::context::tlsv12_client);
        //load_root_certificates(ctx);
        //ctx.set_verify_mode(ssl::verify_peer);

        // These objects perform our I/O
        net::io_context ioc;
        tcp::resolver resolver(ioc);
        beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

        // Set SNI Hostname (many hosts need this to handshake successfully)
        if(! SSL_set_tlsext_host_name(stream.native_handle(), m_host.c_str()))
        {
            beast::error_code ec{
                static_cast<int>(::ERR_get_error()),
                net::error::get_ssl_category()
            };
            throw beast::system_error{ec};
        }

        // init connection
        const auto results = resolver.resolve(m_host, m_port);
        beast::get_lowest_layer(stream).connect(results);
        stream.handshake(ssl::stream_base::client);

        LOG_DEBUG("send http-request to '" + target + "'");

        // create request
        http::request<http::string_body> req{type, target, version};
        req.set(http::field::host, m_host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // add token
        if(m_token != "") {
            req.set("X-Auth-Token", m_token);
        }

        // add body
        if(jsonBody.size() > 0)
        {
           req.body() = jsonBody;
           req.set(http::field::content_type, "application/json");
           req.content_length(jsonBody.size());
           req.prepare_payload();
        }

        // run request
        http::write(stream, req);

        // receive response
        beast::flat_buffer buffer;
        http::response<http::string_body> res;
        http::read(stream, buffer, res);
        response = res.body().c_str();
        statusCode = res.result_int();
        if(statusCode != 200) {
            error.addMeesage(response);
        }

        // Gracefully close the stream
        beast::error_code ec;
        stream.shutdown(ec);
        if(ec == net::error::eof)
        {
            // Rationale:
            // http://stackoverflow.com/questions/25587403/
            //        boost-asio-ssl-async-shutdown-always-finishes-with-an-error
            ec = {};
        }
        if(ec)
        {
            error.addMeesage("failed to close http-connection");
            return statusCode;
        }
    }
    catch(std::exception const& e)
    {
        error.addMeesage("Error while making http-request: "
                         + std::string(e.what()));
        return statusCode;
    }

    return statusCode;
}

} // namespace Hanami
} // namespace Kitsunemimi
