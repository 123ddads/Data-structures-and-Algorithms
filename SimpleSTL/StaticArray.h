#ifndef STATICARRAY_H_
#define STATICARRAY_H_

#include"Array.h"

namespace DTLib {
	template<typename T,int N>
	class StaticArray :public Array<T> {
	protected:
		T m_space[N];
	public:
		StaticArray() {		// 构造函数，m_array指向m_space的首地址，O(1)
			this->m_array = m_space;
		}

		StaticArray(const StaticArray<T, N>& obj) {		// O(N)
			this->m_array = m_space;
			for (int i = 0; i < N; i++) {
				m_space[i] = obj.m_space[i];
			}
		}

		StaticArray& operator = (const StaticArray<T, N>& obj) {	// O(N)
			if (this != &obj) {		// 防止自赋值
				for (int i = 0; i < N; i++) {
					m_space[i] = obj.m_space[i];
				}
			}

			return *this;
		}

		int length()const {		// O(1)
			return N;
		}
	};
}

#endif // !STATICARRAY_H_


