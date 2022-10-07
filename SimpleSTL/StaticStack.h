#ifndef STATICSTACK_H_
#define STATICSTACK_H_

#include"Stack.h"
#include"Exception.h"

// 栈的顺序实现
namespace DTLib {
	template<typename T, int N>
	class StaticStack :public Stack<T> {
	protected:
		T m_space[N];		// 顺序栈实现
		int m_top;			// 栈顶部
		int m_size;			// 栈大小
	public:
		StaticStack() {		// O(1)
			m_top = -1;
			m_size = 0;
		}

		int capacity() const {		// O(1)
			return N;
		}

		void push(const T& e) {		// O(1)
			if (m_size < N) {
				m_space[m_top + 1] = e;
				m_top++;
				m_size++;	
			}
			else {
				THROW_EXCEPTION(InvalidOperationException, "No space in current stack ...");
			}
		}

		void pop() {		// O(1)
			if (m_size > 0) {
				m_top--;
				m_size--;
			}
			else {
				THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
			}
		}

		T top()const {		// O(1)
			if (m_size > 0) {
				return m_space[m_top];
			}
			else {
				THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
			}
		}

		void clear() {		// O(1)
			m_top = -1;
			m_size = 0;
		}

		int size()const {
			return m_size;
		}
	};
}

#endif // !STATICSTACK_H_

