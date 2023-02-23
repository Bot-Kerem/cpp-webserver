#ifndef OWQL_SERVER_HPP
#define OWQL_SERVER_HPP

#include <string_view>
#include <sys/socket.h>

namespace OWQL {
	class ServerBase {
		private:
			int m_socket;
			int check_failed(int, const std::string_view = "") const;

			void main_loop();
	
		protected:
			bool is_running = true;
		public:
			int exec();

			ServerBase(uint16_t port=8972);
			~ServerBase();

			virtual void build() {  }
	};
}

#endif // OWQL_SERVER_HPP

