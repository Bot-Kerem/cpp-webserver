#include <http_parser/parser.hpp>
#include <cassert>
#include <iostream>
#include <spdlog/spdlog.h>

static char const * const str_request = 
R"txt(GET /index.html HTTP/1.1
User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)
Host: www.mozilla.org
Accept-Language: en-us
Accept-Encoding: gzip, deflate
Connection: Keep-Alive
)txt";

using Method = HttpParser::Method;
using ProtocolVersion = HttpParser::ProtocolVersion;

auto main(const int argc, char const * const * argv) -> int {
	const auto request = HttpParser::parse(str_request);

	assert(request.method == Method::GET);
	assert(request.version == ProtocolVersion::HTTP_1_1);
	assert(request.target == "/index.html");
	assert(request.headers.at("User-Agent") == "Mozilla/4.0 (compatible; MSIE5.01; Windows NT)");
	assert(request.headers.at("Host") == "www.mozilla.org");
	assert(request.headers.at("Accept-Language") == "en-us");
	assert(request.headers.at("Accept-Encoding") == "gzip, deflate");
	assert(request.headers.at("Connection") == "Keep-Alive");

	return 0;
}

