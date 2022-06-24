/**
 * @file        websocket_client.cpp
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

#include <libKitsunemimiHanamiSdk/common/websocket_client.h>

#include <libKitsunemimiJson/json_item.h>

namespace Kitsunemimi
{
namespace Hanami
{

/**
 * @brief constructor
 */
WebsocketClient::WebsocketClient() {}

/**
 * @brief destructor
 */
WebsocketClient::~WebsocketClient()
{
    m_websocket->close(websocket::close_code::normal);
    // a 'delete' on the m_websocket-pointer breaks the program,
    // because of bad programming in the websocket-class of the boost beast library
    // TODO: fix the memory-leak
}

/**
 * @brief initialize new websocket-connection to a torii
 *
 * @param socketUuid reference for the
 * @param token token to authenticate socket on the torii
 * @param target name of the target on server-side behind the torii
 * @param host address of the torii
 * @param port port where the server is listen on target-side
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
WebsocketClient::initClient(std::string &socketUuid,
                            const std::string &token,
                            const std::string &target,
                            const std::string &host,
                            const std::string &port,
                            ErrorContainer &error)
{
    try
    {
        // init ssl
        ssl::context ctx{ssl::context::tlsv12_client};
        if(loadCertificates(ctx) == false)
        {
            error.addMeesage("Failed to load certificates for creating Websocket-Client");
            LOG_ERROR(error);
            return false;
        }

        net::io_context ioc;
        tcp::resolver resolver{ioc};
        m_websocket = new websocket::stream<beast::ssl_stream<tcp::socket>>{ioc, ctx};

        // Look up the domain name
        const auto results = resolver.resolve(host, port);
        auto ep = net::connect(get_lowest_layer(*m_websocket), results);

        // Set SNI Hostname (many hosts need this to handshake successfully)
        if(! SSL_set_tlsext_host_name(m_websocket->next_layer().native_handle(), host.c_str()))
            throw beast::system_error(
                beast::error_code(
                    static_cast<int>(::ERR_get_error()),
                    net::error::get_ssl_category()),
                "Failed to set SNI Hostname");

        const std::string address = host + ':' + std::to_string(ep.port());

        m_websocket->next_layer().handshake(ssl::stream_base::client);
        m_websocket->set_option(websocket::stream_base::decorator(
            [](websocket::response_type& res)
            {
                res.set(http::field::server,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " client-websocket-ssl");
            }));

        // Perform the websocket handshake
        m_websocket->handshake(address, "/");

        std::string initialMsg = "";
        initialMsg.append("{\"token\":\"");
        initialMsg.append(token);
        initialMsg.append("\",\"target\":\"");
        initialMsg.append(target);
        initialMsg.append("\"}");

        // Send the message
        m_websocket->binary(true);
        m_websocket->write(net::buffer(initialMsg, initialMsg.size()));

        // Read a message into our buffer
        beast::flat_buffer buffer;
        m_websocket->read(buffer);

        const std::string responseMsg(static_cast<const char*>(buffer.data().data()),
                                      buffer.data().size());

        // parse response
        Kitsunemimi::Json::JsonItem response;
        if(response.parse(responseMsg, error) == false)
        {
            error.addMeesage("Failed to parse response-message from Websocket-init");
            LOG_ERROR(error);
        }

        socketUuid = response.get("uuid").getString();
        return response.get("success").getInt();
    }
    catch(std::exception const& e)
    {
        const std::string msg(e.what());
        error.addMeesage("Error-Message while initilializing Websocket-Client: '" + msg + "'");
        LOG_ERROR(error);
        return false;
    }

    return false;
}

/**
 * @brief send data over websocket-client
 *
 * @param data pointer to data to send
 * @param dataSize number of bytes to send
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
WebsocketClient::sendMessage(const void* data,
                             const uint64_t dataSize,
                             ErrorContainer &error)
{
    try
    {
        // Send the message
        m_websocket->binary(true);
        m_websocket->write(net::buffer(data, dataSize));
    }
    catch(const std::exception &e)
    {
        const std::string msg(e.what());
        error.addMeesage("Error-Message while send Websocket-Data: '" + msg + "'");
        LOG_ERROR(error);
        return false;
    }

    return true;
}

/**
 * @brief WebsocketClient::readMessage
 *
 * @param numberOfByes reference for output of number of read bytes
 * @param error reference for error-output
 *
 * @return nullptr if failed, else pointer
 */
uint8_t*
WebsocketClient::readMessage(uint64_t &numberOfByes,
                             ErrorContainer &error)
{
    try
    {
        // Read a message into our buffer
        beast::flat_buffer buffer;
        m_websocket->read(buffer);

        numberOfByes = buffer.data().size();
        uint8_t* data = new uint8_t[numberOfByes];
        memcpy(data, buffer.data().data(), numberOfByes);

        return data;
    }
    catch(const std::exception &e)
    {
        numberOfByes = 0;
        const std::string msg(e.what());
        error.addMeesage("Error-Message while read Websocket-Data: '" + msg + "'");
        LOG_ERROR(error);
        return nullptr;
    }

    numberOfByes = 0;
    return nullptr;
}

/**
 * @brief load ssl-certificates for ssl-encryption of websocket
 *
 * @param ctx reference to ssl-context
 *
 * @return true, if successful, else false
 */
bool
WebsocketClient::loadCertificates(boost::asio::ssl::context& ctx)
{
    std::string errorMessage = "";
    std::string cert = "-----BEGIN CERTIFICATE-----\n"
                    "MIIErzCCApegAwIBAgIUXUYv/UczoWRYfEB/Lzkrja5vd8kwDQYJKoZIhvcNAQEL\n"
                    "BQAwADAeFw0yMTEyMTAyMjA4NTNaFw0zMTEyMDgyMjA4NTNaMAAwggIiMA0GCSqG\n"
                    "SIb3DQEBAQUAA4ICDwAwggIKAoICAQDZQUWrymom/ogNBIudbS8SMt3yVq5if5d6\n"
                    "3FpPHQMTgjCkq2V9N7E32ECJ3P+CR4GtXz3pv2SyzoAOwzBMJHvglF6d2kuMPCWq\n"
                    "d5/c82JwqC3tIMiE4o47JN55/TYhqHSqQuqfIsmyJyc7k2iM/s5Vzc+jDD5GuPvC\n"
                    "TmHUStESiKgJztr+o9/3TsCumTkRpx/M0htOewqdoT5/VJq3/xYtr+gqpLLOLyHO\n"
                    "CegNAzQCuh6PQ/5jcvshHfKZffjlR7grYshqVxBsaiIlAgt2kUYdyxxS16NIB7ko\n"
                    "XzLYNlVpLQOlxVR+FNSvg9qXW0ZSSJccLzo+Yj51OV9O5xHtF/Cz901Du2ph7mnB\n"
                    "rOBZp0DoOxHzOvsZQz4sef0VTnGoac+3HXTP3rz77xIVYt5dcP5dVRou+vtk0z5X\n"
                    "TJdQbTgCIc9J+nPcRtI7e8U7B43krQXxDvVqUse5JjdiGh25i2FJPUGNGDi5rNC/\n"
                    "lF4F1PBrViKBJnr0nWhVOQNRzehisH3e9vF0vxrNRVzpYXwgaPavr5Jmk5oVM3Mb\n"
                    "/RYNTh/h31Zs2MG0MpdkJoVr6Y4RrpgIY0mkN0p0TTejcrxM5pAzpBYbx3b7d3Rg\n"
                    "S04haZvyCXWG4+1GJ0bu/F5IfConthkz9ceWQPaDDfXCbkBJRvylT6692Lca4c2U\n"
                    "3zooYuaj7QIDAQABoyEwHzAdBgNVHQ4EFgQUvtURt9pLRBZ6dhwVhkzGthk4j/cw\n"
                    "DQYJKoZIhvcNAQELBQADggIBAFkxnqLAiL+jRWH2KBRjc0r8JSAqYdybzsgjmRuu\n"
                    "yvcg79oMRzjywvra66nVXvOsjbO5Tq7NYTTtpeUdVKFYc6Ds3/DHdDwkuQ7AAh2F\n"
                    "D0pRpjMcxQriPKVj7NblBUKewEe8Spb2vFVIItvldMPwCQNDDgEEard7A9QQyeuh\n"
                    "Euvm6s2OHcQgavM2oPsFYHP2ZSoYH4Mebt35ceNU+4RpKXPHEHSE7OV56WxSrcwK\n"
                    "Ww+WkBUFAz6kyQnRFb9RK7/i8RB2ChpChp834oXob8Uq28fCZAi4/3D9Wa/jHVYX\n"
                    "vkwhio0GKdSN0+05J2gV/SbDpgNbNmfcJoRHBGUCm4LHvNM3evqV2TYsq7Gj/VaW\n"
                    "WwKgW9/K6NYABTqgSjFJJ3QaFadPC5BZXLc/aXBQ690vwyto9/DJXO++e3B3b0Uc\n"
                    "z5VrDgQHxHtWhWOEst9Zd5q+z7CJAJcf+e4U6h561ZNDJmoVmlrP5ptQRBEbOwxn\n"
                    "Ig9KhvHCEl/55f9Y5zHq7ZtWstrXrOvSogEc8SbyUP4hIcMBvYPZYe67hdJVNmtL\n"
                    "S1Q36P7CHkKMucKgDgszkQyiJTMklhE/QcUGJXRyji0yIXbLxQHvX30ljAbg1eFy\n"
                    "H6hDZLkm39WIc/J2z4CD2OiKsjERq2tJo09f5zR/VnpeiOZtrc+N0trOFuoql6Xb\n"
                    "TCY4\n"
                    "-----END CERTIFICATE-----";
    std::string key = "-----BEGIN RSA PRIVATE KEY-----\n"
                    "MIIJKAIBAAKCAgEA2UFFq8pqJv6IDQSLnW0vEjLd8lauYn+XetxaTx0DE4IwpKtl\n"
                    "fTexN9hAidz/gkeBrV896b9kss6ADsMwTCR74JRendpLjDwlqnef3PNicKgt7SDI\n"
                    "hOKOOyTeef02Iah0qkLqnyLJsicnO5NojP7OVc3Poww+Rrj7wk5h1ErREoioCc7a\n"
                    "/qPf907Arpk5EacfzNIbTnsKnaE+f1Sat/8WLa/oKqSyzi8hzgnoDQM0Aroej0P+\n"
                    "Y3L7IR3ymX345Ue4K2LIalcQbGoiJQILdpFGHcscUtejSAe5KF8y2DZVaS0DpcVU\n"
                    "fhTUr4Pal1tGUkiXHC86PmI+dTlfTucR7Rfws/dNQ7tqYe5pwazgWadA6DsR8zr7\n"
                    "GUM+LHn9FU5xqGnPtx10z968++8SFWLeXXD+XVUaLvr7ZNM+V0yXUG04AiHPSfpz\n"
                    "3EbSO3vFOweN5K0F8Q71alLHuSY3YhoduYthST1BjRg4uazQv5ReBdTwa1YigSZ6\n"
                    "9J1oVTkDUc3oYrB93vbxdL8azUVc6WF8IGj2r6+SZpOaFTNzG/0WDU4f4d9WbNjB\n"
                    "tDKXZCaFa+mOEa6YCGNJpDdKdE03o3K8TOaQM6QWG8d2+3d0YEtOIWmb8gl1huPt\n"
                    "RidG7vxeSHwqJ7YZM/XHlkD2gw31wm5ASUb8pU+uvdi3GuHNlN86KGLmo+0CAwEA\n"
                    "AQKCAgEAw+xHRnuOa4gTbZnxxpDWaFUTLx7YuN9T3mqlzr7dLVS1RWuEZP46haAx\n"
                    "46I3kmemHJHNpeUCjPYJKkcAYUptpMRo53Ybt2XumeKzenDLD8m7USPFcYFWvyOq\n"
                    "ttyRWp0uSPV73PNkbZM9oE55dN29ekfWvrWl2+WqtTo2o1qtXUd8MwwnFoj2y3Jr\n"
                    "9YkcnDzZQr8f/RCdLDZjxDSqKtCSUbVXbE2HKsX6eHMan9GJsAPk11J8MXdZ3i3B\n"
                    "wIaIVUzuW8ID91J47yxvimxjphOw5eFrs5HgIG9GnY/srGujbuw3Y+GnJuTmQTpp\n"
                    "gSHBMydfjv1QSz4SEWkh+GgOFIEIgbm72ro6oEK767Ji0U8K3hePNVkxwX1G6I7M\n"
                    "CLUoKv81kwYkne26qSyotNkdmfFuCjm/XrhkgR45Qt0T1pHE4ptAgCldUK+hI9vg\n"
                    "UMsv4tkcVd5CFr4G9rJAHj108aQBcqnq0TRSbZokfwnlNbHIlr01roLaOAL3cNXP\n"
                    "lTUFHjGxhXvHe65jXiGv4gsJbTPThmdwcz3XasMUIaFpmVnmNVw9T+2TgDsI+zHr\n"
                    "8K9jHRoQNz4SgPO09+HlWJHoiuR/tZJvcKFeYM0/v4XsbYQVca37g9L4tzpLndyp\n"
                    "ROZtVk/8eBwSwBXxY01a8cYh72Z2+Au9X6Q4Qtywx6fM6dUEpwECggEBAPk4d+HL\n"
                    "Zngk8DATeUwLv7cM3+bP/CCil4pttonfPN1sERASZLM3paffxKZj50WBptqRQiV8\n"
                    "f3lwECsXEtydPUv4X1PAGbb5P15LUonEn1IEJ5dqvdITKXCBD3RJlhOlmzbRJw6V\n"
                    "YIFIWoD25YbPSj5zhv4eZQq5imyxJfPwsaKo1QnaSgq+SK9EqfOoNyv+HbA/UWlV\n"
                    "1RJFMD2m1+tTw/kyf78aFgo31w/ecNlwFNuRs5UQtcl2keK1WN+LqGg+cCZLki4t\n"
                    "8oHDjXiD0twKDjSIr2+gUpCBIzK5sT1nXX8Ztvf2c0D8H9Xl3NoqgVuMrK5aqEMH\n"
                    "W18bHgGtiIdIQGECggEBAN8qM1Z5jliCuxej7YHeq7THNYu8mNsD2+DWzHZOhNjW\n"
                    "cN8VEz05tsCKICV0W7eg36VmraWrscA6Bf4Mh8y6Yx2/BtCtOB+MzgGdgplz7oE0\n"
                    "pKWND3xOSHFbkTa2R/gsr4JfwIsrLy/Nn9OU3ll8QMPpG2dmI2tJL1Fq1s3j0nay\n"
                    "6zgHouvgwZYlibgFGTeP5y9do9E5vVwRBtj8In5+rEGF9ulaNv8bLoudcuRwcJdm\n"
                    "fBu4+7Vd8sJl+FB/XBMy7E+Nal19LUJfhJ2HyUMU0stLn80YCYB/FooWGpYH5DB9\n"
                    "HB6cfbUCxtBs+cjYDO1kxIuUBRVe6LdcadEC8fUTvw0CggEAXcxtAmSlim6Mn+uU\n"
                    "aZS6cVC9LIf3IulPE+C7JSUKKWQ0/9GMaQ92n7pOrzlGoBhuDjFBrg4vhCszSqSC\n"
                    "itn7ag5vAnx4sS8aNIkw5X1FYX8Cz7BzBRAFNry8bk4L2BUqV/VcN9bs3Xu35HYI\n"
                    "aTa3gM3GbvpNmT2/5ay+1hMvKENW+0BXQbfgb2bueDBFo58e2WjbYUPWz+uOfoW/\n"
                    "GmkKh04EWo6c4PenT+eunYfbsdAiwOXrJYok2ija7DgKCEIHv8INoKfWcBSDuGoV\n"
                    "AJAgTJFtRhwXNyADeWH+XVf8DoxFGwp80maSLNU4zDvXN/e4Pl8MmT25nA/+uS7x\n"
                    "BcmhwQKCAQAOQCqhFggR/N8npk8vYOHEHIh90OBN9BQhanYKA/+VvTPd+wGMglf6\n"
                    "OZfN7H1C36IIdOMX1jv2k334eCJf33Me3ij4QGd6FEq/bah+Vhnf5FWzQKvBe1pC\n"
                    "6t7+CGvWHDxk7epkuLA9tDrFjxcXzchw+jzGwI34dubvowvuf+Lbs5czr8EmoOab\n"
                    "yO/fcWvn0Weo7ajdXnuKGog+aPNm8n3bfUuEIT+r0LeLMNW6Yre940x/lLN2JHax\n"
                    "FUPjGA7wJutSNSyapbizKVhVmusuPnErjDu7JBLPQs5UqQ6vj/dxZTvbdJDOc0vw\n"
                    "2VSmD63bpviqFRyx/aqMsvkK4M5EoSstAoIBAGub5WcG7+BpmbFql6J3fas/YiGp\n"
                    "396V24SadLW8IV69pLKjujvREQrX2OB4CI0SyNTGoBP+WIXCu1nLAxBjP2QQtoch\n"
                    "Za9naWCuQmXXNVH9U4jinDENHy4KZHRlGmWpdEyrt4ZS2i8bpI1mjr4pVKxydzDb\n"
                    "kj1eEQ2wxyFLqrLXRsW4+41ye1Drc5MQUCwS4Px9by2V6KuXjKFOhnqJD0/Pq8hR\n"
                    "k1P8K8tlWuvmiOKiL4UnJ8lBbGBeoGwibMxyBu9dr6ZwvZCV+y740TLkSyoT6LYV\n"
                    "YCNFo/pI+Y7XDlAuq3dxTdYm5E+M2gP9fGP9lCWeDkx1eqIw7wWk0GwHaSE=\n"
                    "-----END RSA PRIVATE KEY-----";

    const std::string dh = "-----BEGIN DH PARAMETERS-----\n"
                           "MIIBCAKCAQEArzQc5mpm0Fs8yahDeySj31JZlwEphUdZ9StM2D8+Fo7TMduGtSi+\n"
                           "/HRWVwHcTFAgrxVdm+dl474mOUqqaz4MpzIb6+6OVfWHbQJmXPepZKyu4LgUPvY/\n"
                           "4q3/iDMjIS0fLOu/bLuObwU5ccZmDgfhmz1GanRlTQOiYRty3FiOATWZBRh6uv4u\n"
                           "tff4A9Bm3V9tLx9S6djq31w31Gl7OQhryodW28kc16t9TvO1BzcV3HjRPwpe701X\n"
                           "oEEZdnZWANkkpR/m/pfgdmGPU66S2sXMHgsliViQWpDCYeehrvFRHEdR9NV+XJfC\n"
                           "QMUk26jPTIVTLfXmmwU0u8vUkpR7LQKkwwIBAg==\n"
                           "-----END DH PARAMETERS-----\n";


    ctx.set_options(boost::asio::ssl::context::default_workarounds |
                    boost::asio::ssl::context::no_sslv2 |
                    boost::asio::ssl::context::single_dh_use);

    ctx.use_certificate_chain(boost::asio::buffer(cert.data(), cert.size()));

    ctx.use_private_key(boost::asio::buffer(key.data(), key.size()),
                        boost::asio::ssl::context::file_format::pem);

    ctx.use_tmp_dh(boost::asio::buffer(dh.data(), dh.size()));

    return true;
}

}  // namespace Hanami
}  // namespace Kitsunemimi
