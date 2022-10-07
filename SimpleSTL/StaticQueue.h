#ifndef STATICQUEUE_H_
#define STATICQUEUE_H_

#include"Queue.h"
#include"Exception.h"

// ԭ������ģ��ʵ�ֶ���, ˳�����
namespace DTLib {
	template<typename T, int N>		// ����ģ�����
	class StaticQueue :public Queue<T> {
	protected:
		T m_space[N];			// ������ģ����пռ�
		int m_front;			// ��ͷ
		int m_rear;				// ��β
		int m_length;			// ���г���
	public:
		StaticQueue() {			// ��ʼ��
			m_front = 0;
			m_rear = 0;
			m_length = 0;
		}

		int capacity()const {
			return N;
		}

		void add(const T& e) {			// ��β����, O(1)
			if (m_length < N) {
				m_space[m_rear] = e;
				m_rear = (m_rear + 1) % N;			// ����ѭ�������ķ�ʽ��Ч�ʸ��ߣ��ʵ���˼
				m_length++;
			}
			else {
				THROW_EXCEPTION(InvalidOperationException, "No space in current queue ...");
			}
		}

		void remove() {			// ��ͷɾ���� O(1)
			if (m_length > 0) {
				m_front = (m_front + 1) % N;		// ѭ�����������Ч��
				m_length--;
			}
			else {
				THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
			}
		}

		T front()const {			// ��ȡ��ͷԪ�أ���������, O(1)
			if (m_length > 0) {
				return m_space[m_front];
			}
			else {
				THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
			}
		}

		void clear() {		// �������, O(1)
			m_front = 0;
			m_rear = 0;
			m_length = 0;
		}

		int length()const {		// ���ض��г���, O(1)
			return m_length;
		}
	};
}

#endif // !STATICQUEUE_H_

