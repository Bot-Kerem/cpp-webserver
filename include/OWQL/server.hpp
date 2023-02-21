#ifndef OWQL_SERVER_HPP
#define OWQL_SERVER_HPP

#include <string_view>
#include <sys/socket.h>

class ServerBase {
	private:
		int m_socket;
		int check_failed(int, const std::string_view = "") const;
	public:
		ServerBase();
		~ServerBase();
		int exec();

		virtual void build() {  }
};

#endif // OWQL_SERVER_HPP

