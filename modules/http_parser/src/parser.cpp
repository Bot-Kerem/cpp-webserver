#include "parser.hpp"
#include <stdexcept>

using namespace HttpParser;

static const std::map<std::string, Method> methods {{
		{ "GET" 		, Method::GET			}
	,	{ "HEAD"		, Method::HEAD 		}
	,	{ "POST"		, Method::POST 		}
	,	{ "PUT"			, Method::PUT		 	}
	,	{ "DELETE"	, Method::DELETE 	}
	,	{ "CONNECT"	, Method::CONNECT }
	,	{ "OPTIONS"	, Method::OPTIONS }
	,	{ "TRACE"		, Method::TRACE 	}
}};

static const std::map<std::string, ProtocolVersion> protocol_versions {{
		{ "HTTP/0.9",  ProtocolVersion::HTTP_0_9 }
	,	{ "HTTP/1.0",  ProtocolVersion::HTTP_1_0 }
	,	{ "HTTP/1.1",  ProtocolVersion::HTTP_1_1 }
	,	{ "HTTP/2.0",  ProtocolVersion::HTTP_2_0 }
	,	{ "HTTP/3.0",  ProtocolVersion::HTTP_3_0 }
}};

HttpRequest HttpParser::parse(std::string_view str) {
	HttpRequest request;
	if (str.starts_with("PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n")) {
		request.version = ProtocolVersion::HTTP_2_0;
		return request;
	}

	int i = 0;
	int num_space = 0;
	std::string temp_str;
	for (; i < str.length(); i++) {
		if (str[i] == ' ') {
			if (num_space == 0) {
				request.method = methods.at(temp_str);
			} else if (num_space == 1) {
				request.target = temp_str;
			}
			num_space++;
			temp_str.clear();
		}
		else if (str[i] == '\n') {
			temp_str.erase(temp_str.find_last_not_of(' ') + 1);
			request.version = protocol_versions.at(temp_str);
			temp_str.clear();
			i++;
			break;
		} else {
			temp_str.push_back(str[i]);
		}
	}

	std::string header;
	// parse headers
	for (; i < str.length(); i++) {
		if (str[i] == '\n') {
			request.headers.insert({header, temp_str});

			temp_str.clear();
			header.clear();
			if (str[i+1] == '\n' || str[i+1] == '\0') {
				i+=2;
				break;
			}
		} else if (str[i] == ':' && header.empty()) {
			i += 1;
			header = temp_str;
			temp_str.clear();
		} else {
			temp_str.push_back(str[i]);
		}
		if (!temp_str.empty()) {
		}
	}

	return request;
}

