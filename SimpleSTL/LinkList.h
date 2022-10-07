#ifndef LINKLIST_H_
#define LINKLIST_H_
#include"List.h"
#include"Object.h"
#include"Exception.h"

// ������
namespace DTLib {
	template<typename T>
	class LinkList :public List<T> {		
	protected:
		struct Node :public Object {
			T value;		// �ýڵ�ֵ
			Node* next;		// ��һ���ڵ�
		};
		mutable struct :public Object {		// ����������������Ĺ��캯��������һ��������ͬ�������࣬�����÷�ָ���͵Ĺ��캯��
			char reserved[sizeof(T)];
			Node* next;
		}m_head;
		int m_length;
		int m_step;			// �α�����λ��
		Node* m_current;	// �α�

		Node* Position(int i)const {	// �Ż�	,O(n)
			Node* ret = reinterpret_cast<Node*>(&m_head);
			for (int p = 0; p < i; p++) {
				ret = ret->next;
			}
			return ret;
		}

		virtual Node* create() {		// ��װ֮˼��
			return new Node;
		}

		virtual void destory(Node* pn) {
			delete pn;
		}
	public:
		LinkList() {	// ������ʼ����Ա����
			m_head.next = nullptr;
			m_length = 0;
			m_step = 0;
			m_current = nullptr;
		}

		bool insert(int i, const T& e)  {	  // ָ��λ�ò���ڵ�
			bool ret = ((0 <= i) && (i <= m_length));
			if (ret) {
				Node* node = create();
				if (node != nullptr) {
					Node* current = Position(i);	// O(n)
					node->value = e;
					node->next = current->next;
					current->next = node;
					m_length++;		// ����һ
				}
				else {
					THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element ...");
				}
			}
			return ret;
		}

		bool insert(const T& e) {		// ��β������
			return insert(m_length, e);
		}
		
		int find(const T& e)const {		// ����ָ��Ԫ��ֵλ�ã�O(n)
			int ret = -1;
			Node* node = m_head.next;
			int i = 0;
			while (node)  {
				if (node->value == e) {
					ret = i;
					break;
				}
				else {
					node = node->next;
					i++;
				}
			}
			return ret;
		}

		bool remove(int i) {		// ɾ��Ԫ��
			bool ret = ((0 <= i) && (i < m_length));
			if (ret) {
				Node* current = Position(i);	// O(n)
				Node* toDel = current->next;
				if (m_current == toDel) {
					m_current = toDel->next;
				}
				current->next = toDel->next;
				m_length--;
				destory(toDel);
			}
			return ret;
		}

		bool set(int i, const T& e) {
			bool ret = ((0 <= i) && (i < m_length));
			if (ret) {
				Position(i)->next->value = e;	// ��Ϊ�и�����ͷ��㣬��Ϊ��һ��λ��
			}
			return ret;
		}

		virtual T get(int i)const {
			T ret;
			if (get(i, ret)) {
				return ret;
			}
			else {
				THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter i to get element ...");
			}
		}

		bool get(int i, T& e)const {		// O(n)
			bool ret = ((0 <= i) && (i < m_length));
			if (ret) {
				e = Position(i)->next->value;
			}
			return ret;
		}

		int length()const {
			return m_length;
		}

		void clear() {		// O(n)
			while (m_head.next) {
				Node* toDel = m_head.next;
				m_head.next = toDel->next;
				m_length--;
				destory(toDel);
			}
		}

		virtual bool move(int i, int step = 1) {
			bool ret = (0 <= i) && (i < m_length) && (step > 0);
			if (ret) {
				m_current = Position(i)->next;
				m_step = step;
			}
			return ret;
		}

		virtual bool end() {
			return (m_current == nullptr);
		}

		T current() {
			if (!end()) {
				return m_current->value;
			}
			else {
				THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
			}
		}

		virtual bool next() {
			int i = 0;
			while ((i < m_step) && !end()) {
				m_current = m_current->next;
				i++;
			}

			return (i == m_step);
		}

		~LinkList() {		// O(n)
			clear();
		}
	};
}

#endif // !LINKLIST_H_

