#ifndef HTTP_PARSER_ENUMS_HPP
#define HTTP_PARSER_ENUMS_HPP

namespace HttpParser {
	enum class ProtocolVersion {
			HTTP_0_9
		,	HTTP_1_0
		,	HTTP_1_1
		,	HTTP_2_0 // unsupported
		, HTTP_3_0 // unsupported
	};

	enum class Method {
		// https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods
			GET
		,	HEAD
		,	POST
		,	PUT
		,	DELETE
		,	CONNECT
		,	OPTIONS
		,	TRACE
	};
} // namespace HttpParser

#endif // HTTP_PARSER_ENUMS_HPP

