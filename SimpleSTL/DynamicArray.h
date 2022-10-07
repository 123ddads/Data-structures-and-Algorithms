#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_

#include"Array.h"
#include"Exception.h"

namespace DTLib {
	template<typename T>
	class DynamicArray :public Array<T> {
	protected:
		int m_length;

		T* Copy(T* array, int len, int newLen) {	// �ڶѿռ��������µ��ڴ棬��ִ�п���������ʱ�临�Ӷ�O(min(len,newLen))==>O(n)
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

		void Init(T* array, int length) {	// ������ʱ�ĳ�ʼ��������O(1)
			if (array != nullptr) {
				this->m_array = array;
				this->m_length = length;
			}
			else {
				THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object ...");
			}
		}
	public:
		DynamicArray(int length = 0) {		// ���캯����O(1)��������Ĭ�ϲ���
			Init(new T[length], length);
		}

		DynamicArray(const DynamicArray<T>& obj) {		// �������죬O(n)
			Init(Copy(obj.m_array, obj.m_length, obj.m_length), obj.length);
		}

		DynamicArray<T>& operator=(const DynamicArray<T>& obj) {	// ���ظ�ֵ������
			if (this != &obj) {		// �����Ը�ֵ
				Update(Copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
			}

			return *this;
		}

		int length()const {
			return m_length;
		}

		void resize(int length) {	// ��ָ̬�������С
			if (length != m_length) {
				Update(Copy(this->m_array, m_length, length), length);	 
			}
		}
		
		~DynamicArray() {		// ��������
			delete[] this->m_array;
		}
	};
}

#endif // !DYNAMICARRAY_H_

