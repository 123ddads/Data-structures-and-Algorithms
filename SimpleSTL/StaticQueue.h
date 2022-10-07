#ifndef STATICQUEUE_H_
#define STATICQUEUE_H_

#include"Queue.h"
#include"Exception.h"

// 原生数组模拟实现队列, 顺序队列
namespace DTLib {
	template<typename T, int N>		// 采用模板参数
	class StaticQueue :public Queue<T> {
	protected:
		T m_space[N];			// 数组来模拟队列空间
		int m_front;			// 队头
		int m_rear;				// 队尾
		int m_length;			// 队列长度
	public:
		StaticQueue() {			// 初始化
			m_front = 0;
			m_rear = 0;
			m_length = 0;
		}

		int capacity()const {
			return N;
		}

		void add(const T& e) {			// 队尾插入, O(1)
			if (m_length < N) {
				m_space[m_rear] = e;
				m_rear = (m_rear + 1) % N;			// 采用循环计数的方式，效率更高，邮电意思
				m_length++;
			}
			else {
				THROW_EXCEPTION(InvalidOperationException, "No space in current queue ...");
			}
		}

		void remove() {			// 队头删除， O(1)
			if (m_length > 0) {
				m_front = (m_front + 1) % N;		// 循环计数，提高效率
				m_length--;
			}
			else {
				THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
			}
		}

		T front()const {			// 获取队头元素，但不出队, O(1)
			if (m_length > 0) {
				return m_space[m_front];
			}
			else {
				THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
			}
		}

		void clear() {		// 清除队列, O(1)
			m_front = 0;
			m_rear = 0;
			m_length = 0;
		}

		int length()const {		// 返回队列长度, O(1)
			return m_length;
		}
	};
}

#endif // !STATICQUEUE_H_

