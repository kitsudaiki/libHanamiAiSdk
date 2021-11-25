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

#include "request.h"

#include <libKitsunemimiJson/json_item.h>

namespace Kitsunemimi
{
namespace Hanami
{

Request::Request() {}

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
Request::init(const std::string &host,
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
    if(m_host == "")
    {
        if(getEnvVar(m_host, "HANAMI_ADDRESS") == false) {
            return false;
        }
    }

    // get target-port
    if(m_port == "")
    {
        if(getEnvVar(m_port, "HANAMI_PORT") == false) {
            return false;
        }
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
 * @brief Request::sendGetRequest
 * @param response reference for response-output
 * @param path path to call
 * @param vars variables as string for the request-path
 * @param error reference for error-output
 *
 * @return false, if something went wrong while sending or token-request failed, else true
 */
bool
Request::sendGetRequest(std::string &response,
                        const std::string &path,
                        const std::string &vars,
                        ErrorContainer &error)
{
    return makeRequest(response, http::verb::get, path, vars, "", error);
}

/**
 * @brief Request::sendPostRequest
 * @param response reference for response-output
 * @param path path to call
 * @param vars variables as string for the request-path
 * @param body json-body as string
 * @param error reference for error-output
 * @return false, if something went wrong while sending or token-request failed, else true
 */
bool
Request::sendPostRequest(std::string &response,
                         const std::string &path,
                         const std::string &vars,
                         const std::string &body,
                         ErrorContainer &error)
{
    return makeRequest(response, http::verb::post, path, vars, body, error);
}

/**
 * @brief Request::sendPutRequest
 * @param response reference for response-output
 * @param path path to call
 * @param vars variables as string for the request-path
 * @param body json-body as string
 * @param error reference for error-output
 * @return false, if something went wrong while sending or token-request failed, else true
 */
bool
Request::sendPutRequest(std::string &response,
                        const std::string &path,
                        const std::string &vars,
                        const std::string &body,
                        ErrorContainer &error)
{
    return makeRequest(response, http::verb::put, path, vars, body, error);
}

/**
 * @brief Request::sendDeleteRequest
 * @param response reference for response-output
 * @param path path to call
 * @param vars variables as string for the request-path
 * @param error reference for error-output
 *
 * @return false, if something went wrong while sending or token-request failed, else true
 */
bool
Request::sendDeleteRequest(std::string &response,
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
Request::getEnvVar(std::string &content,
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
Request::requestToken(ErrorContainer &error)
{
    // get user for access
    if(m_user == "")
    {
        if(getEnvVar(m_user, "HANAMI_USER") == false) {
            return false;
        }
    }

    // get password for access
    if(m_pw == "")
    {
        if(getEnvVar(m_pw, "HANAMI_PW") == false) {
            return false;
        }
    }

    // build request-path
    std::string path = "control/misaka/token?user_name=";
    path.append(m_user);
    path.append("&pw=");
    path.append(m_pw);

    // make token-request
    std::string response;
    if(makeRequest(response, http::verb::get, path, "", error) == false)
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
Request::makeRequest(std::string &response,
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
    std::string target = path + "?token=" + m_token;
    if(vars != "") {
        target.append("&" + vars);
    }

    // send request
    if(makeRequest(response, type, target, jsonBody, error) == false) {
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
        target = path + "?token=" + m_token;
        if(vars != "") {
            target.append("&" + vars);
        }

        // try request again
        if(makeRequest(response, type, target, jsonBody, error) == false) {
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
bool
Request::makeRequest(std::string &response,
                     const http::verb type,
                     const std::string &target,
                     const std::string &jsonBody,
                     ErrorContainer &error)
{
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

        // run request
        http::request<http::string_body> req{type, target, version};
        req.set(http::field::host, m_host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        if(jsonBody.size() > 0) {
           req.body() = jsonBody;
        }
        http::write(stream, req);

        // receive response
        beast::flat_buffer buffer;
        http::response<http::string_body> res;
        http::read(stream, buffer, res);
        std::cout << res << std::endl;
        response = res.body().c_str();

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
        if(ec) {
            error.addMeesage("failed to close http-connection");
            return false;
        }
    }
    catch(std::exception const& e)
    {
        error.addMeesage("Error while making http-request: "
                         + std::string(e.what()));
        return false;
    }

    return true;
}

}  // namespace Hanami
}  // namespace Kitsunemimi
