#ifndef DualCircleList_H_
#define DualCircleList_H_

#include"LinuxList.h"
#include"DualLinkList.h"
#include"Exception.h"


// 基于Linux内核表的双向循环链表
namespace DTLib {
	template<typename T>
	class DualCircleList: public DualLinkList<T> {
	protected:
		struct Node :public Object {
			list_head head;
			T value;
		};

		list_head m_head;		// 头结点
		list_head* m_current;	// 当前节点

		list_head* position(int i) const {		
			list_head* ret = const_cast<list_head*>(&m_head);	// const成员函数中不能直接取成员地址，这里采用了强转

			for (int p = 0; p < i; p++) {
				ret = ret->next;
			}

			return ret;
		}

		int mod(int i)const {
			return (this->m_length == 0) ? 0 : (i % this->m_length);
		}
	public:
		DualCircleList() {
			this->m_length = 0;
			this->m_step = 1;

			m_current = nullptr;
			INIT_LIST_HEAD(&m_head);
		}

		// 尾插法
		bool insert(const T& e) {
			return insert(this->m_length, e);
		}

		bool insert(int i, const T& e) {
			bool ret = true;
			Node* node = new Node();

			i = i % (this->m_length + 1);		// 归一化操作，效率更高

			if (node != nullptr) {
				node->value = e;
				
				list_add_tail(&node->head, position(i)->next);
				
				this->m_length++;
			}
			else {
				THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element ...");
			}
			return ret;
		}

		bool remove(int i) {
			bool ret = true;

			i = mod(i);

			ret = ((0 <= i) && (i < this->m_length));

			if (ret) {
				list_head* toDel = position(i)->next;

				if (m_current == toDel) {
					m_current = toDel->next;
				}

				list_del(toDel);

				this->m_length--;

				delete list_entry(toDel, Node, head);
			}

			return ret;
		}

		bool set(int i, const T& e) {
			bool ret = true;
			i = mod(i);
			ret =((0 <= i) && (i < this->m_length));
			if (ret) {
				list_entry(position(i)->next, Node, head)->value = e;
			}
			return ret;
		}

		T get(int i)const {
			T ret;
			if (get(i, ret)) {
				return ret;
			}
			else {
				THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter i to get element ...");
			}
		}

		bool get(int i, T& e)const {	
			bool ret = true;
			i = mod(i);
			ret = ((0 <= i) && (i < this->m_length));
			if (ret) {
				e = list_entry(position(i)->next, Node, head)->value;
			}
			return ret;
		}

		int find(const T& e)const {		// 查找，O(n)
			int ret = -1;
			int i = 0;
			list_head* slider = nullptr;

			list_for_each(slider, &m_head) {
				if (list_entry(slider, Node, head)->value == e) {
					ret = i;
					break;
				}

				i++;
			}
			return ret;
		}

		int length()const {
			return this->m_length;
		}

		void clear() {
			while (this->m_length > 0) {
				remove(0);
			}
		}

		bool move(int i, int step = 1) {
			bool ret = (step > 0);

			i = mod(i);
			
			ret = ret && ((0 <= i) && (i < this->m_length));

			if (ret) {
				m_current = position(i)->next;

				this->m_step = step ;
			}
			return ret;
		}

		bool end() {
			return (m_current == nullptr) || (this->m_length == 0);
		}

		virtual T current() {
			if (!end()) {
				return list_entry(m_current, Node, head)->value;
			}
			else {
				THROW_EXCEPTION(InvalidOperationException, "No value in current position ...");
			}
		}

		bool next() {
			int i = 0;

			while ((i < this->m_step) && !end()) {
				if (m_current != &m_head) {		//	跳过头结点
					m_current = m_current->next;
					i++;
				}
				else {
					m_current = m_current->next;	
				}
			}

			if (m_current == &m_head) {
				m_current = m_current->next;
			}

			return (i == this->m_step);
		}

		bool pre() {
			int i = 0;

			while ((i < this->m_step) && !end()) {
				if (m_current != &m_head) {		//	跳过头结点
					m_current = m_current->prev;
					i++;
				}
				else {
					m_current = m_current->prev;
				}
			}

			if (m_current == &m_head) {
				m_current = m_current->prev;
			}

			return (i == this->m_step);
		}

		~DualCircleList() {
			clear();
		}
	};
}

#endif // !DualCircleList
