#ifndef _SMARTPOINTER_H_
#define _SMARTPOINTER_H_

#include<iostream>
#include"Pointer.h"

namespace DTLib {
	template<typename T>
	class SmartPointer :public Pointer<T> {
	public:
		SmartPointer(T* p = nullptr):Pointer<T>(p) {}	// 直接调用父类的构造函数

		SmartPointer(const SmartPointer<T>& obj) {	//拷贝构造函数
			std::cout << "SmartPointer的拷贝构造函数" << std::endl;
			this->m_pointer = obj.m_pointer;
			const_cast<SmartPointer<T>&>(obj).m_pointer = nullptr;
		}

		SmartPointer<T>& operator=(const SmartPointer<T>& obj) {	//深拷贝
			std::cout << "SmartPointer的赋值操作符重载" << std::endl;
			if (this != &obj) {
				T* p = this->m_pointer;		// 为了异常安全，先将堆空间给到临时变量
				this->m_pointer = obj.m_pointer;
				const_cast<SmartPointer<T>&>(obj).m_pointer = nullptr;
				delete p;
			}
			return *this;
		}

		~SmartPointer() {
			delete this->m_pointer;
		}
	};
}


#endif // !_SMARTPOINTER_H_