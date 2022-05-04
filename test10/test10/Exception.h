#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

namespace DTlib {
#define THROW_EXCEPTION(e,m) (throw e(m,__FILE__,__LINE__))	//宏定义抛出异常

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
		Exception& operator=(const Exception& e);	//要深拷贝

		virtual const char* message() const;
		virtual const char* location() const; 

		virtual ~Exception();	//C+规定：定义了虚构函数，都得去实现
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

