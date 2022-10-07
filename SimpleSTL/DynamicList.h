#ifndef _DYNAMICLIST_H_
#define _DYNAMICLIST_H_

#include"SeqList.h"

namespace DTLib {
	template<typename T>
	class DynamicList :public SeqList<T> {
	protected:
		int m_capacity;		// ˳��洢�ռ�Ĵ�С
	public:
		DynamicList(int capacity) {		// ����ռ�
			this->m_array = new T[capacity];
			if (this->m_array != NULL) {
				this->m_length = 0;
				this->m_capacity = capacity;
			}
			else {
				THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicList object...");	//���쳣���ռ䲻��
			}
		}

		int capacity()const {
			return m_capacity;
		}

		/*��������˳��洢�ռ�Ĵ�С*/
		void resize(int capacity) {
			if (m_capacity != capacity) {
				T* array = new T[capacity];		//����һ�ζѿռ�
				if (array != NULL) {	//�ڴ�����ɹ�
					int length = (this->m_length < capacity ? this->m_length : capacity);
					for (int i = 0; i < length; i++) {
						array[i] = this->m_array[i];
					}

					T* temp = this->m_array;	// �쳣��ȫ�������ռ任��ȫ

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

		~DynamicList() {	// �黹�ռ�
			delete[] this->m_array;
		}
	};
}

#endif // !_DYNAMICLIST_H_
