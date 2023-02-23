#include "parser.hpp"
#include <iostream>

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
			continue;
		}
		else if (str[i] == '\n') {
			if (temp_str.back() == ' ') {
				temp_str.pop_back();
			}
			request.version = protocol_versions.at(temp_str);
			temp_str.clear();
			i++;
			break;
		}
		temp_str.push_back(str[i]);
	}

	//for (; i < str.length(); i++) {
	//}
	return request;
}

