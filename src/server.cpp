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

	char buffer[1024];
	size_t buf_len = read(client, buffer, 1024);
	auto request = HttpParser::parse({buffer, buf_len});
	spdlog::info("Target: {}", request.target);
}

OWQL::ServerBase::ServerBase(uint16_t port) {
	// TODO: Make a config struct for creation info
	const auto protocol = OWQL::Protocol::IPv4;
	const auto backlog = 1000;

	// Create a tcp socket
	spdlog::info("Creating socket");
	m_socket = check_failed(socket(protocol, SOCK_STREAM, 0), "Socket couldn't created");

	// Assign IP and PORT
	sockaddr_in server_addr;
	server_addr.sin_family 			= protocol;
	server_addr.sin_addr.s_addr	= htonl(INADDR_ANY);
	server_addr.sin_port				= htons(port);

	// Bind socket
	spdlog::info("Binding socket at port: {}", port);
	check_failed(bind(m_socket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)), "Binding socket failed");

	// Listen
	spdlog::info("Server listening with backlog: {}", backlog);
	listen(m_socket, backlog);
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

