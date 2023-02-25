#ifndef OWQL_SERVER_HPP
#define OWQL_SERVER_HPP

#include "enums.hpp"
#include <http_parser/parser.hpp>
#include <string_view>
#include <sys/socket.h>

namespace OWQL {
	class ServerBase {
		struct Config {
			uint16_t 	port 		 = 8972;
			int 			backlog  = 1000;
			Protocol	protocol = IPv4;
		};

		private:
			int m_socket;
			int check_failed(int, const std::string_view = "") const;

			void main_loop();
	
		protected:
			bool is_running = true;
			virtual void build() {  }
			virtual void handle_request(HttpParser::HttpRequest request) {  }
		public:
			int exec();

			ServerBase(Config config);
			~ServerBase();

	};
}

#endif // OWQL_SERVER_HPP

