#ifndef _DYNAMICLIST_H_
#define _DYNAMICLIST_H_

#include"SeqList.h"

namespace DTLib {
	template<typename T>
	class DynamicList :public SeqList<T> {
	protected:
		int m_capacity;		// 顺序存储空间的大小
	public:
		DynamicList(int capacity) {		// 申请空间
			this->m_array = new T[capacity];
			if (this->m_array != NULL) {
				this->m_length = 0;
				this->m_capacity = capacity;
			}
			else {
				THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicList object...");	//抛异常：空间不足
			}
		}

		int capacity()const {
			return m_capacity;
		}

		/*重新设置顺序存储空间的大小*/
		void resize(int capacity) {
			if (m_capacity != capacity) {
				T* array = new T[capacity];		//开辟一段堆空间
				if (array != NULL) {	//内存申请成功
					int length = (this->m_length < capacity ? this->m_length : capacity);
					for (int i = 0; i < length; i++) {
						array[i] = this->m_array[i];
					}

					T* temp = this->m_array;	// 异常安全，牺牲空间换安全

					this->m_array = array;		
					this->m_length = length;
					this->m_capacity = capacity;

					delete[] temp;
				}
				else {
					THROW_EXCEPTION(NoEnoughMemoryException, "No memory to resize DynamicList object...");
				}
			}
		}

		~DynamicList() {	// 归还空间
			delete[] this->m_array;
		}
	};
}

#endif // !_DYNAMICLIST_H_
