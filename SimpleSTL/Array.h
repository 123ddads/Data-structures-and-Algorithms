#ifndef ARRAY_H_
#define ARRAY_H_

#include"Object.h"
#include"Exception.h"

namespace DTLib {
	template<typename T>
	class Array :public Object {
	protected:
		T* m_array;
	public:
		virtual bool set(int i, const T& e) {	// ָ��λ������ֵ��ʱ�临�Ӷ�O(1)
			bool ret = ((0 <= i) && (i < length()));
			if (ret) {
				m_array[i] = e;
			}

			return ret;
		}

		virtual bool get(int i, T& e)const {	// ��ȡָ��λ�õ�ֵ��ʱ�临�Ӷ�O(1)
			bool ret = ((0 <= i) && (i < length()));
			if (ret) {
				e = m_array[i];
			}

			return ret;
		}

		T& operator[](int i) {		// O(1)
			if ((0 <= i) && (i < length())) {
				return m_array[i];
			}
			else {
				THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
			}
		}

		T operator[](int i)const {	// O(1)
			return (const_cast<Array<T>&>(*this))[i];
		}

		virtual int length()const = 0;	// ���麯��
	};
}

#endif // !ARRAY_H_

