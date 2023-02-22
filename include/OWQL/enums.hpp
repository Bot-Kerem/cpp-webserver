#ifndef OWQL_ENUMS_HPP
#define OWQL_ENUMS_HPP

#include <sys/socket.h>
#include <sys/types.h>

namespace OWQL {
	enum Protocol: int {
		// IPv4 internet protocol
		IPv4 	= AF_INET,
		// IPv6 internet protocol
		IPv6 	= AF_INET6,
		// Local communication
		Local = AF_UNIX, // same as AF_LOCAL
	};

	enum class RequestType {
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
};


#endif // OWQL_ENUMS_HPP

