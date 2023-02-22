#ifndef OWQL_HTTP_HPP
#define OWQL_HTTP_HPP

#include "enums.hpp"
#include <string>
#include <map>

namespace OWQL {
	struct Request {
		RequestType type;
		std::map<std::string, std::string> headers;
	};
}
#endif // OWQL_HTTP_HPP

