#ifndef LINKQUEUE_H_
#define LINKQUEUE_H_

#include"Queue.h"
#include"Exception.h"
#include"LinuxList.h"

/*
	采用了Linux内核链表来实现队列，提高效率
	开始使用的是链表来实现的。
*/

// 队列的链式存储实现
namespace DTLib {
	template<typename T>		// 采用模板参数
	class LinkQueue :public Queue<T> {
	protected:
		struct Node :public Object {
			list_head head;
			T value;
		};

		list_head m_head;
		int m_length;
	public:
		LinkQueue() {			// O(1)
			m_length = 0;

			INIT_LIST_HEAD(&m_head);
		}

		void add(const T& e) {			// 入队, O(1)
			Node* node = new Node();

			if (node != nullptr) {
				node->value = e;

				list_add_tail(&node->head, &m_head);	// O(1)

				m_length++;
			}
			else {
				THROW_EXCEPTION(InvalidOperationException, "No memory to add new element ...");
			}
		}

		void remove() {			// 出队, O(1)
			if (m_length > 0) {
				list_head* toDel = m_head.next;

				list_del(toDel);

				m_length--;

				delete list_entry(toDel, Node, head);
			}
			else {
				THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
			}
		}

		T front()const {			// 获取队头元素，但不出队, O(1)
			if (m_length > 0) {
				return list_entry(m_head.next, Node, head)->value;
			}
			else {
				THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
			}
		}

		void clear() {		// 清除队列, O(n)
			while(m_length > 0) {
				remove();
			}
		}

		int length()const {		// 返回队列长度, O(1)
			return m_length;
		}

		~LinkQueue() {		// O(n)
			clear();
		}
	};
}

#endif // !LINKQUEUE_H_

