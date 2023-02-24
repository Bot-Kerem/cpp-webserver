#ifndef HTTP_PARSER_HPP
#define HTTP_PARSER_HPP

#include "enums.hpp"

#include <string>
#include <map>
#include <string_view>

namespace HttpParser {
	class HttpRequest {
		public:
			Method method;
			ProtocolVersion version;
			std::string target;
			std::map<std::string, std::string> headers;
			std::string content;
	};

	HttpRequest parse(std::string_view str);
} // namespace HttpParser

#endif // HTTP_PARSER_HPP

