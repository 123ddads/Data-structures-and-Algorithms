#include"Exception.h"
#include<cstring>
#include<stdlib.h>
#pragma warning(disable:4996)	//直接忽略4996错误

namespace DTlib { 
	void Exception::init(const char* message, const char* file, int line) {
		m_message = strdup(message);	

		if (file != NULL) {
			char sl[16] = { 0 };
			itoa(line, sl, 10);

			m_location = static_cast<char*>(malloc(strlen(file) + strlen(sl) + 2));
			m_location = strcpy(m_location, file);	//复制	
			m_location = strcat(m_location, ":");	//拼接
			m_location = strcat(m_location, sl);	//出错的行号
		}
		else {
			m_location = NULL;
		}
	}

	Exception::Exception(const char* message) {
		init(message, NULL, 0);
	}

	Exception::Exception(const char* file, int line) {
		init(NULL, file, line);
	}

	Exception::Exception(const char* message, const char* file, int line) {
		init(message, file, line);
	}

	Exception::Exception(const Exception& e) {	
		m_message = strdup(e.m_message);
		m_location = strdup(e.m_location);
	}

	Exception& Exception::operator=(const Exception& e) {	//深拷贝
		if (this != &e) {
			free(m_message);
			free(m_location);

			m_message = strdup(e.m_message);
			m_location = strdup(e.m_location);
		}
		return *this;
	}

	const char* Exception::message() const {
		return m_message;
	}

	const char* Exception::location() const {
		return m_location;
	}

	Exception::~Exception() {
		free(m_message);
		free(m_location);
	}
}