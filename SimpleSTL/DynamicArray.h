#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_

#include"Array.h"
#include"Exception.h"

namespace DTLib {
	template<typename T>
	class DynamicArray :public Array<T> {
	protected:
		int m_length;

		T* Copy(T* array, int len, int newLen) {	// 在堆空间中申请新的内存，并执行拷贝操作，时间复杂度O(min(len,newLen))==>O(n)
			T* ret = new T[newLen];
			if (ret != nullptr) {
				int size = (len < newLen ? len : newLen);
				for (int i = 0; i < size; i++) {
					ret[i] = array[i];
				}
			}
			return ret;
		}

		void Update(T* array, int len) {	// O(1)
			if (array != nullptr) {
				T* temp = this->m_array;

				this->m_array = array;
				this->m_length = len;

				delete[] temp;
			}
			else {
				THROW_EXCEPTION(NoEnoughMemoryException, "No memory to update DynamicArray object ...");
			}
		}

		void Init(T* array, int length) {	// 对象构造时的初始化操作，O(1)
			if (array != nullptr) {
				this->m_array = array;
				this->m_length = length;
			}
			else {
				THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object ...");
			}
		}
	public:
		DynamicArray(int length = 0) {		// 构造函数，O(1)，给的是默认参数
			Init(new T[length], length);
		}

		DynamicArray(const DynamicArray<T>& obj) {		// 拷贝构造，O(n)
			Init(Copy(obj.m_array, obj.m_length, obj.m_length), obj.length);
		}

		DynamicArray<T>& operator=(const DynamicArray<T>& obj) {	// 重载赋值操作符
			if (this != &obj) {		// 避免自赋值
				Update(Copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
			}

			return *this;
		}

		int length()const {
			return m_length;
		}

		void resize(int length) {	// 动态指定数组大小
			if (length != m_length) {
				Update(Copy(this->m_array, m_length, length), length);	 
			}
		}
		
		~DynamicArray() {		// 析构函数
			delete[] this->m_array;
		}
	};
}

#endif // !DYNAMICARRAY_H_

