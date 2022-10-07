#ifndef _SEQLIST_H_
#define _SEQLIST_H_

#include"List.h"
#include"Exception.h"

// ������
namespace DTLib {
	template<typename T>
	class SeqList :public List<T> {
	protected:
		T* m_array;		// ˳��洢�ռ�
		int m_length;	// ��ǰ���Ա���
	public:
		bool insert(int i, const T& e) {	// ����
			bool ret = ((0 <= i) && (i <= m_length));	// �жϲ����Ƿ�Ϸ�
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

		int find(const T& e)const {		// ����
			int ret = -1;
			for (int i = 0; i < m_length; i++) {
				if (m_array[i] == e) {
					ret = i;
					break;
				}
			}
			return ret;
		}

		bool remove(int i) {	// ɾ��
			bool ret = ((0 <= i) && (i < m_length));
			if (ret) {
				for (int p = i; p < m_length - 1; p++) {
					m_array[p] = m_array[p + 1];
				}
				m_length--;
			}
			return ret;
		}

		bool set(int i, const T& e) {	// ��ֵ
			bool ret = ((i <= 0) && (i < m_length));
			if (ret) {
				m_array[i] = e;
			}
			return ret;
		}

		bool get(int i, T& e)const {	// ����ֵ
			bool ret = ((0 <= i) && (i < m_length));
			if (ret) {
				e = m_array[i];
			}
			return ret;
		}

		int length()const {		// ��ȡ��
			return m_length;
		}

		void clear() {		// ������Ա�
			m_length = 0;
		}

		// ˳��洢���Ա��������ʷ�ʽ
		T& operator[] (int i) {
			bool ret = ((0 <= i) && (i < m_length));
			if (ret) {
				return m_array[i];
			}
			else {	
				THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");	//�׳��쳣��Խ��
			}
		}
		T operator[] (int i)const {
			return (const_cast<SeqList<T>&>(*this))[i];
		}

		// ˳��洢�ռ������
		virtual int capacity() const = 0;	
	};
}

#endif // !_SEQLIST_H_

