/*
 *Author:GeneralSandman
 *Code:https://github.com/GeneralSandman/TinyWeb
 *E-mail:generalsandman@163.com
 *Web:www.dissigil.cn
 */

/*---XXX---
 *
 ****************************************
 *
 */

#include <tiny_base/log.h>
#include <tiny_core/protocol.h>
#include <tiny_http/http_parser.h>
#include <tiny_http/http_protocol.h>
#include <tiny_http/http_responser.h>

WebProtocol::WebProtocol()
    : Protocol()
    , m_nKeepAlive(false)
{
    LOG(Debug) << "class WebProtocol constructor\n";
}

void WebProtocol::connectionMade()
{
    LOG(Info) << "get a new connection\n";
}

void WebProtocol::dataReceived(const std::string& data)
{
    LOG(Info) << "WebProtocol get data\n";

    HttpParserSettings settings;
    HttpRequest* result = new HttpRequest;
    int begin = 0;

    HttpParser parser(&settings);
    parser.setType(HTTP_TYPE_REQUEST);

    int tmp = parser.execute(data.c_str(),
        begin,
        data.size(),
        result);

    bool res = (tmp == -1) ? false : true;
    if (res) {
        HttpResponser responser;
        std::string data;

        responser.response(result, data);

        // Funciton of basic class.
        sendMessage(data);
    }

    delete result;
}

void WebProtocol::connectionLost()
{
    LOG(Info) << "lost a connection\n";
}

WebProtocol::~WebProtocol()
{
    LOG(Debug) << "class WebProtocol destructor\n";
}

RegistProtocol(WebProtocol);
