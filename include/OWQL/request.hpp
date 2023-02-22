#ifndef OWQL_HTTP_HPP
#define OWQL_HTTP_HPP

#include "char_array.hpp"

#include <string>
#include <map>

class Request {
	private:
	public:
		std::map<std::string_view, std::string_view> headers;

		void parse(const CharArray buffer) {
			for (const auto& c: buffer) {

			}
		}

		Request(const CharArray buffer) {
			parse(buffer);
		}
};

#endif // OWQL_HTTP_HPP

