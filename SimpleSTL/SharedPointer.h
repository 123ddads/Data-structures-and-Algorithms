#ifndef SHAREDPOINTER_H_
#define SHAREDPOINTER_H_

#include<cstdlib>
#include"Pointer.h"
#include"Exception.h"

namespace DTLib {
	template<typename T>
	class SharedPointer :public Pointer<T> {
	protected:
		int* m_ref;			// 计数机制成员指针

		void assign(const SharedPointer<T>& obj) {
			this->m_ref = obj.m_ref;
			this->m_pointer = obj.m_pointer;
			if (this->m_ref) {
				(*this->m_ref)++;
			}
		}
	public:
		SharedPointer(T* p = nullptr):m_ref(nullptr) {
			if (p) {
				this->m_ref = static_cast<int*>(std::malloc(sizeof(int)));
				if (this->m_ref) {
					*(this->m_ref) = 1;
					this->m_pointer = p;
				}
				else {
					THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create SharedPointer Object ...");
				}
			}
		}

		SharedPointer(const SharedPointer<T>& obj):Pointer<T>(nullptr) {		// 拷贝构造函数
			assign(obj);
		}

		SharedPointer<T>& operator=(const SharedPointer<T>& obj) {	// 避免自赋值，深拷贝，赋值操作符重载
			if (this != &obj) {
				clear();
				assign(obj);
			}

			return *this;
		}

		void clear() {		// 将当前指针置为空
			T* toDel = this->m_pointer;
			int* ref = this->m_ref;

			this->m_pointer = nullptr;
			this->m_ref = nullptr;

			if (ref) {
				(*ref)--;
				if (*ref == 0) {
					free(ref);

					delete toDel;
				}
			}
		}

		~SharedPointer() {
			clear();
		}
	};

	template<typename T>	// 全局函数，重载比较操作符
	bool operator == (const SharedPointer<T>& l, const SharedPointer<T>& r) {
		return (l.get() == r.get());
	}

	template<typename T>
	bool operator != (const SharedPointer<T>& l, const SharedPointer<T>& r) {
		return !(l == r);
	}
}

#endif // !SHAREDPOINTER_H_

