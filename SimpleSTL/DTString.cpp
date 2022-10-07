#include"DTString.h"
#include<cstring>
#include<cstdlib>
#include"Exception.h"

using namespace std;

// 字符串
namespace DTLib {
	// 初始化
	void String::init(const char* s) {
		m_str = _strdup(s);
		
		if (m_str) {
			m_length = strlen(m_str);	
		}
		else {
			THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create String object ...");
		}
	}

	// 比对函数
	bool String::equal(const char* l, const char* r, int len)const {
		bool ret = true;

		for (int i = 0; (i < len) && (ret); i++) {
			ret = ret && (l[i] == r[i]);
		}

		return ret;
	}

	String::String(char c) {
		char s[] = { c,'\0' };
		init(s);
	}

	String::String() {
		init("");
	}

	String::String(const char* s) {
		init(s ? s : "");
	}
	
	String::String(const String& s) {
		init(s.m_str);
	}

	int String::length()const {
		return m_length;
	}

	const char* String::str()const {
		return m_str;
	}

	// 判断字符串是否以s开头
	bool String::startWith(const char* s)const {
		bool ret = (s != nullptr);

		if (ret) {
			int len = strlen(s);

			ret = (len < m_length) && equal(m_str, s, len);
		}

		return ret;
	}

	bool String::startWith(const String& s)const {
		return startWith(s.m_str);
	}

	// 判断字符串是否以s结束
	bool String::endOf(const char* s)const {
		bool ret = (s != nullptr);

		if (ret) {
			int len = strlen(s);
			char* str = m_str + (m_length - len);

			ret = (len < m_length) && equal(str, s, len);
		}

		return ret;
	}

	// 去掉字符串两端字符
	String& String::trim() {
		int b = 0;
		int e = m_length - 1;

		while (m_str[b] == ' ') b++;
		while (m_str[e] == ' ') e--;

		if (b == 0) {
			m_str[e + 1] = '\0';
			m_length = e + 1;
		}
		else {
			for (int i = 0, j = b; j <= e; i++, j++) {
				m_str[i] = m_str[j];
			}

			m_str[e - b + 1] = '\0';
			m_length = e - b + 1;
		}

		return *this;
	}

	bool String::endOf(const String& s)const {
		return endOf(s.m_str);
	}

	// 在指定位置处插入字符串
	String& String::insert(int i, const char* s) {
		if ((0 <= i) && (i <= m_length)) {
			if ((s != nullptr) && (s[0] != '\0')) {
				int len = strlen(s);
				char* str = reinterpret_cast<char*>(malloc(len + m_length + 1));

				if (str != nullptr) {
					strncpy(str, m_str, i);
					strncpy(str + i, s, len);
					strncpy(str + i + len, m_str + i, m_length - i);

					str[m_length + len] = '\0';

					free(m_str);

					m_str = str;
					m_length = m_length + len;
				}
				else {
					THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert String value ...");
				}
			}
		}
		else {
			THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
		}
		
		return *this;
	}

	String& String::insert(int i, const String& s){
		return insert(i, s.m_str);
	}

	char& String::operator [](int i) {
		if ((0 <= i) && (i < m_length)) {
			return m_str[i];
		}
		else {
			THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
		}
	}

	char String::operator [](int i)const {
		return (const_cast<String&>(*this))[i];
	}

	bool String::operator == (const String& s)const {
		return (strcmp(m_str, s.m_str) == 0);
	}

	bool String::operator == (const char* s)const {
		return (strcmp(m_str, s ? s : "") == 0);
	}

	bool String::operator != (const String& s)const {
		return !(*this == s);
	}

	bool String::operator != (const char* s)const {
		return !(*this == s);
	}

	bool String::operator > (const String& s)const {
		return (strcmp(m_str, s.m_str) > 0);
	}

	bool String::operator > (const char* s)const {
		return (strcmp(m_str, s ? s : "") > 0);
	}

	bool String::operator < (const String& s)const {
		return (strcmp(m_str, m_str) < 0);
	}

	bool String::operator < (const char* s)const {
		return (strcmp(m_str, s ? s : "") < 0);
	}

	bool String::operator >= (const String& s)const {
		return (strcmp(m_str, s.m_str) >= 0);
	}

	bool String::operator >= (const char* s)const {
		return (strcmp(m_str, s ? s : "") >= 0);
	}

	bool String::operator <= (const String& s)const {
		return (strcmp(m_str, s.m_str) <= 0);
	}

	bool String::operator <= (const char* s)const {
		return (strcmp(m_str, s ? s : "") <= 0);
	}

	String String::operator + (const String& s)const {
		return (*this + s.m_str);
	}

	String String::operator + (const char* s)const {
		String ret;
		int len = m_length + strlen(s);
		char* str = reinterpret_cast<char *>(malloc(len + 1));

		if (str) {
			strcpy(str, m_str);
			strcat(str, s ? s : "");

			free(ret.m_str);

			ret.m_str = str;
			ret.m_length = len;
		}
		else {
			THROW_EXCEPTION(NoEnoughMemoryException, "No memory to add String object ...");
		}

		return ret;
	}

	String& String::operator += (const String& s) {
		return (*this = *this + s.m_str);
	}

	String& String::operator += (const char* s){
		return (*this = *this + s);
	}

	String& String::operator = (const String& s) {
		return (*this = s.m_str);
	}

	String& String::operator = (const char* s) {
		if (m_str != s) {
			char* str = strdup(s ? s : "");

			if (str) {
				free(m_str);

				m_str = str;
				m_length = strlen(m_str);
			}
			else {
				THROW_EXCEPTION(NoEnoughMemoryException, "No memory to assign new String value ...");
			}
		}

		return *this;
	}

	String& String::operator = (char c) {
		char s[] = { c, '\0' };

		return (*this = s);
	}

	String::~String() {
		free(m_str);
	}
}