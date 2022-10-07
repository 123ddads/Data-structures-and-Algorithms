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
		virtual bool set(int i, const T& e) {	// 指定位置设置值，时间复杂度O(1)
			bool ret = ((0 <= i) && (i < length()));
			if (ret) {
				m_array[i] = e;
			}

			return ret;
		}

		virtual bool get(int i, T& e)const {	// 获取指定位置的值，时间复杂度O(1)
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

		virtual int length()const = 0;	// 纯虚函数
	};
}

#endif // !ARRAY_H_

