#include "server.hpp"

#include <spdlog/spdlog.h>

int ServerBase::exec() {
	spdlog::info("Started server");
	spdlog::info("Building...");
	build();
	spdlog::info("Program closed with exit code: {}", 0);
	return 0;
}

