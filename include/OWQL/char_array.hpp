#ifndef OWQL_CHAR_ARRAY_HPP
#define OWQL_CHAR_ARRAY_HPP

#include <cstdlib>
#include <iostream>
#include <spdlog/spdlog.h>

class CharArray {
	private:
		char* 	m_data;
		size_t 	m_size;
		
	public:
		
		CharArray(size_t size) noexcept {
			m_data = reinterpret_cast<char*>(malloc(size));
			m_size = size;
		}

		~CharArray() {
			if (m_data) {
				// BUG: set m_data nullptr on move
				free(m_data);
			}
		}

		inline void resize(size_t size) noexcept {
			void* data = realloc(m_data, size);
			if (data != nullptr) {
				std::cout << "DELETED\n" << '\n';
				m_data = reinterpret_cast<char*>(data);
				m_size = size;
			}
		}

		std::vector<std::string_view> slice(char slice) const noexcept {
			std::vector<std::string_view> result;
			std::string_view str(m_data, m_size);

			size_t pos = 0;
  		while ((pos = str.find(slice)) != std::string_view::npos) {
    		result.push_back(str.substr(0, pos));

    		str.remove_prefix(pos + 1);
  		}

			if (!str.empty()) {
				result.push_back(str);
			}
			return result;
		}

		inline char* data() noexcept {
			return m_data;
		}
		inline char* data() const noexcept {
			return m_data;
		}
		inline char* begin() noexcept {
			return m_data;
		}
		inline char* begin() const noexcept {
			return m_data;
		}
		inline char* end() noexcept {
			return m_data + m_size;
		}
		inline char* end() const noexcept {
			return m_data + m_size;
		}
};

#endif

