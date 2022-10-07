#ifndef LINKSTACK_H_
#define LINKSTACK_H_

#include"Stack.h"
#include"LinkList.h"

// 链式栈的存储实现
namespace DTLib {
	template<typename T>
	class LinkStack :public Stack<T> {
	protected:
		LinkList<T> m_list;
	public:
		void push(const T& e) {		// 入栈(头插法), O(1)
			m_list.insert(0, e);
		}

		void pop() {		// 出栈， O(1)
			if (m_list.length() > 0) {
				m_list.remove(0);
			}
			else {
				THROW_EXCEPTION(InvalidOperationException, "No elment in current stack ...");
			}
		}

		T top()const {		// O(1)
			if (m_list.length() > 0) {
				m_list.get(0);
			}
			else {
				THROW_EXCEPTION(InvalidOperationException, "No elment in current stack ...");
			}
		}

		void clear() {		// O(n)
			m_list.clear();
		}

		int size()const {		// O(1)
			return m_list.length();
		}
	};
}

#endif // !LINKSTACK_H_

