#include <OWQL/server.hpp>

auto main(const int argc, char const * const * argv) -> int {
	OWQL::ServerBase s;
	return s.exec();
}
