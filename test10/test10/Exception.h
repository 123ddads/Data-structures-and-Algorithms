#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

namespace DTlib {
#define THROW_EXCEPTION(e,m) (throw e(m,__FILE__,__LINE__))	//�궨���׳��쳣

	class Exception {
	protected:
		char* m_message;
		char* m_location;

		void init(const char* message, const char* file, int line);
	public:
		Exception(const char* message);
		Exception(const char* file, int line);
		Exception(const char* message, const char* file, int line);

		Exception(const Exception& e);	
		Exception& operator=(const Exception& e);	//Ҫ���

		virtual const char* message() const;
		virtual const char* location() const; 

		virtual ~Exception();	//C+�涨���������鹹����������ȥʵ��
	};

	class ArithmeticException :public Exception {
	public:
		ArithmeticException() :Exception(0) { }
		ArithmeticException(const char* message) :Exception(message) { }
		ArithmeticException(const char* file, int line) :Exception(file, line) { }
		ArithmeticException(const char* message, const char* file, int line) :Exception(message, file, line) { }

		ArithmeticException(const ArithmeticException& e) :Exception(e) { }

		ArithmeticException& operator=(const ArithmeticException& e) {
			Exception::operator=(e);

			return *this;
		}
	};
}

#endif // !_EXCEPTION_H_

