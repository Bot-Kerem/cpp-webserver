#ifndef OWQL_SERVER_HPP
#define OWQL_SERVER_HPP


class ServerBase {
	private:
	public:
		int exec();

		virtual void build() {  }
};

#endif // OWQL_SERVER_HPP

