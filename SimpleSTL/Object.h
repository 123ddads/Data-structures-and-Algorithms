#ifndef _OBJECT_H_
#define _OBJECT_H_

namespace DTLib {
	class Object {
	public:
		void* operator new(size_t size) throw();	// 创建单个对象，异常安全
		void operator delete(void* p);
		void* operator new[](size_t size) throw();	// 不允许抛出任何异常，即该函数是异常安全的
		void operator delete[](void* p);
		bool operator == (const Object& obj);
		bool operator != (const Object& obj);
		virtual ~Object() = 0;
	};
}

#endif // !_OBJECT_H_