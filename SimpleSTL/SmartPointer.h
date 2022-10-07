#ifndef _SMARTPOINTER_H_
#define _SMARTPOINTER_H_

#include<iostream>
#include"Pointer.h"

namespace DTLib {
	template<typename T>
	class SmartPointer :public Pointer<T> {
	public:
		SmartPointer(T* p = nullptr):Pointer<T>(p) {}	// ֱ�ӵ��ø���Ĺ��캯��

		SmartPointer(const SmartPointer<T>& obj) {	//�������캯��
			std::cout << "SmartPointer�Ŀ������캯��" << std::endl;
			this->m_pointer = obj.m_pointer;
			const_cast<SmartPointer<T>&>(obj).m_pointer = nullptr;
		}

		SmartPointer<T>& operator=(const SmartPointer<T>& obj) {	//���
			std::cout << "SmartPointer�ĸ�ֵ����������" << std::endl;
			if (this != &obj) {
				T* p = this->m_pointer;		// Ϊ���쳣��ȫ���Ƚ��ѿռ������ʱ����
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