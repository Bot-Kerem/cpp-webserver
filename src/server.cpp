#include "server.hpp"
#include "enums.hpp"

#include <http_parser/parser.hpp>

#include <spdlog/spdlog.h>

#include <iostream>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

int OWQL::ServerBase::exec() {
	spdlog::info("Started server");
	spdlog::info("Building...");
	spdlog::set_level(spdlog::level::level_enum::trace);
	build();

	while (is_running) {
		main_loop();
	}

	spdlog::info("Program closed with exit code: {}", 0);
	return 0;
}

void OWQL::ServerBase::main_loop() {
	spdlog::info("Waiting for connections");
	sockaddr_in cli;
	socklen_t cli_len = sizeof(cli);
	int client = accept(m_socket, reinterpret_cast<sockaddr*>(&cli), &cli_len);
	spdlog::info("Connection acccepted shutting down the server");
	is_running = false;

	size_t buf_len;
	char buffer[1024];
	std::string request_str;
	while ((buf_len = read(client, buffer, 1024))) {
		spdlog::info("Reading {} bytes", buf_len);
		request_str.append(buffer, buf_len);
		if (buf_len < sizeof(buffer)) {
			break;
		}
	}

	auto request = HttpParser::parse(request_str);
	request.client = client;
	handle_request(request);
}

OWQL::ServerBase::ServerBase(Config config) {
	// TODO: Make a config struct for creation info

	// Create a tcp socket
	spdlog::info("Creating socket");
	m_socket = check_failed(socket(config.protocol, SOCK_STREAM, 0), "Socket couldn't created");

	// Assign IP and PORT
	sockaddr_in server_addr;
	server_addr.sin_family 			= config.protocol;
	server_addr.sin_addr.s_addr	= htonl(INADDR_ANY);
	server_addr.sin_port				= htons(config.port);

	// Bind socket
	spdlog::info("Binding socket at port: {}", config.port);
	check_failed(bind(m_socket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)), "Binding socket failed");

	// Listen
	spdlog::info("Server listening with backlog: {}", config.backlog);
	listen(m_socket, config.backlog);
}

OWQL::ServerBase::~ServerBase() {
	close(m_socket);
}

int OWQL::ServerBase::check_failed(int proc, const std::string_view msg) const {
	if (proc < 0) {
		throw std::runtime_error(msg.data());
	}
	return proc;
}

