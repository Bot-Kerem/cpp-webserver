#include "server.hpp"
#include "enums.hpp"

#include <spdlog/spdlog.h>

#include <iostream>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

int ServerBase::exec() {
	spdlog::info("Started server");
	spdlog::info("Building...");
	build();

	while (is_running) {
		main_loop();
	}

	spdlog::info("Program closed with exit code: {}", 0);
	return 0;
}

void ServerBase::main_loop() {
	spdlog::info("Waiting for connections");
	sockaddr_in cli;
	socklen_t cli_len = sizeof(cli);
	int client = accept(m_socket, reinterpret_cast<sockaddr*>(&cli), &cli_len);
	spdlog::info("Connection acccepted shutting down the server");
	is_running = false;

	auto request = get_request(client);
}

Request ServerBase::get_request(int client) {
	return {};
}

ServerBase::ServerBase() {
	// TODO: Make a config struct for creation info
	const auto protocol = OWQL::Protocol::IPv4;
	const auto port = 8972;
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

ServerBase::~ServerBase() {
	close(m_socket);
}

int ServerBase::check_failed(int proc, const std::string_view msg) const {
	if (proc < 0) {
		throw std::runtime_error(msg.data());
	}
	return proc;
}

