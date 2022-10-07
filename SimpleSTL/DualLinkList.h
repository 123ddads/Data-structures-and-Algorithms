#ifndef DUALLINKLIST_H_
#define DUALLINKLIST_H_

#include"List.h"
#include"Exception.h"

// ˫������
namespace DTLib {
	template<typename T>
	class DualLinkList :public List<T> {
	protected:
		struct Node :public Object {
			T value;		// �ýڵ�ֵ
			Node* next;		// ��һ���ڵ�
			Node* pre;
		};
		mutable struct :public Object {		// ����������������Ĺ��캯��������һ��������ͬ�������࣬�����÷�ָ���͵Ĺ��캯��
			char reserved[sizeof(T)];
			Node* next;
			Node* pre;
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

		virtual Node* create() {		// ��װ
			return new Node;
		}

		virtual void destory(Node* pn) {
			delete pn;
		}
	public:
		DualLinkList() {	// ������ʼ����Ա����
			m_head.next = nullptr;
			m_length = 0;
			m_step = 0;
			m_current = nullptr;
		}


		bool insert(const T& e) {		// ��β������
			return insert(m_length, e);
		}

		bool insert(int i, const T& e) {	  // ָ��λ�ò���ڵ�
			bool ret = ((0 <= i) && (i <= m_length));
			if (ret) {
				Node* node = create();
				if (node != nullptr) {
					Node* current = Position(i);	// O(n)
					Node* next = current->next;	

					node->value = e;

					node->next = next;
					current->next = node;

					if (current != reinterpret_cast<Node*>(&m_head)) {
						node->pre = current;
					}
					else {
						node->pre = nullptr;
					}

					if (next != nullptr) {
						next->pre = node;
					}

					m_length++;		// ����һ
				}
				else {
					THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element ...");
				}
			}
			return ret;
		}

		int find(const T& e)const {		// ���ң�O(n)
			int ret = -1;
			Node* node = m_head.next;
			int i = 0;
			while (node) {
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

		bool remove(int i) {
			bool ret = ((0 <= i) && (i < m_length));
			if (ret) {
				Node* current = Position(i);	// O(n)
				Node* toDel = current->next;
				Node* next = toDel->next;

				if (m_current == toDel) {
					m_current = next;
				}

				current->next = next;

				if (next != nullptr) {
					next->pre = toDel->pre;
				}

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
			while (m_length > 0) {
				remove(0);
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

		virtual bool pre() {
			int i = 0;

			while ((i < m_step) && !end()) {
				m_current = m_current->pre;
				i++;
			}

			return (i == m_step);
		}

		~DualLinkList() {		// O(n)
			clear();
		}
	};
}

#endif // !DUALLINKLIST_H_
