#ifndef POINTER_H_
#define POINTER_H_

#include"Object.h"

namespace DTLib {
	template<typename T>
	class Pointer :public Object {		// Pointer 仍然是抽象类
	protected:
		T* m_pointer;
	public:
		Pointer(T* p = nullptr) {	// 构造函数采用默认参数，防止属性指向非法空间
			m_pointer = p;
		}

		T* operator->() {
			return m_pointer;
		}

		T& operator*() {
			return *m_pointer;
		}

		const T* operator->() const {
			return m_pointer;
		}

		const T& operator*() const {
			return *m_pointer;
		}

		bool isNull() const {
			return (m_pointer == nullptr);
		}

		T* get() const {
			return m_pointer;
		}
	};
}

#endif // !POINTER_H_

