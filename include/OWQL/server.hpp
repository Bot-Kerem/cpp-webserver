#ifndef OWQL_SERVER_HPP
#define OWQL_SERVER_HPP

#include <string_view>
#include <sys/socket.h>
#include <tuple>
#include <array>

#include "request.hpp"

namespace OWQL {
	class ServerBase {
		private:
			int m_socket;
			int check_failed(int, const std::string_view = "") const;
			Request get_request(int client);
			std::tuple<std::array<char, 1024>, size_t> read_request(int client);

			void main_loop();
	
		protected:
			bool is_running = true;
		public:
			int exec();

			ServerBase();
			~ServerBase();

			virtual void build() {  }
	};
}

#endif // OWQL_SERVER_HPP

