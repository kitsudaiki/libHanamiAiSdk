#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

namespace Kitsunemimi
{
namespace Hanami
{

class WebsocketClient
{
public:
    WebsocketClient();
    ~WebsocketClient();

    bool initClient(std::string &socketUuid,
                    const std::string &token,
                    const std::string &target,
                    const std::string &host,
                    const std::string &port);
    bool sendMessage(const void* data,
                     const uint64_t dataSize);

private:
    websocket::stream<beast::ssl_stream<tcp::socket>>* m_websocket = nullptr;
    bool loadCertificates(boost::asio::ssl::context &ctx);
};

}
}

#endif // WEBSOCKETCLIENT_H
