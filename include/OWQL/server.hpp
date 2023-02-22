#ifndef OWQL_SERVER_HPP
#define OWQL_SERVER_HPP

#include <string_view>
#include <sys/socket.h>

#include "char_array.hpp"

class ServerBase {
	private:
		int m_socket;
		int check_failed(int, const std::string_view = "") const;
		CharArray read_message(int client);

		void main_loop();
	
	protected:
		bool is_running = true;
	public:
		int exec();

		ServerBase();
		~ServerBase();

		virtual void build() {  }
};

#endif // OWQL_SERVER_HPP

