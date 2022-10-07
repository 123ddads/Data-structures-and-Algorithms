#ifndef _SEQLIST_H_
#define _SEQLIST_H_

#include"List.h"
#include"Exception.h"

// 抽象类
namespace DTLib {
	template<typename T>
	class SeqList :public List<T> {
	protected:
		T* m_array;		// 顺序存储空间
		int m_length;	// 当前线性表长度
	public:
		bool insert(int i, const T& e) {	// 插入
			bool ret = ((0 <= i) && (i <= m_length));	// 判断插入是否合法
			ret = ret && (m_length < capacity());
			
			if (ret) {
				for (int p = m_length - 1; p >= i; p--) {
					m_array[p + 1] = m_array[p];
				}

				m_array[i] = e;
				m_length++;
			}
			return ret;
		}

		bool insert(const T& e) {
			return insert(m_length, e);
		}

		int find(const T& e)const {		// 查找
			int ret = -1;
			for (int i = 0; i < m_length; i++) {
				if (m_array[i] == e) {
					ret = i;
					break;
				}
			}
			return ret;
		}

		bool remove(int i) {	// 删除
			bool ret = ((0 <= i) && (i < m_length));
			if (ret) {
				for (int p = i; p < m_length - 1; p++) {
					m_array[p] = m_array[p + 1];
				}
				m_length--;
			}
			return ret;
		}

		bool set(int i, const T& e) {	// 设值
			bool ret = ((i <= 0) && (i < m_length));
			if (ret) {
				m_array[i] = e;
			}
			return ret;
		}

		bool get(int i, T& e)const {	// 返回值
			bool ret = ((0 <= i) && (i < m_length));
			if (ret) {
				e = m_array[i];
			}
			return ret;
		}

		int length()const {		// 获取表长
			return m_length;
		}

		void clear() {		// 清空线性表
			m_length = 0;
		}

		// 顺序存储线性表的数组访问方式
		T& operator[] (int i) {
			bool ret = ((0 <= i) && (i < m_length));
			if (ret) {
				return m_array[i];
			}
			else {	
				THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");	//抛出异常：越界
			}
		}
		T operator[] (int i)const {
			return (const_cast<SeqList<T>&>(*this))[i];
		}

		// 顺序存储空间的容量
		virtual int capacity() const = 0;	
	};
}

#endif // !_SEQLIST_H_

