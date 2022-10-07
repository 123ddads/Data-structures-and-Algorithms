#ifndef STATICLINKLIST_H_

#include"LinkList.h"

namespace DTLib {
	template<typename T,int N>
	class StaticLinkList :public LinkList<T> {
	protected:
		typedef typename LinkList<T>::Node Node;

		struct SNode :Node {
			void* operator new(size_t size, void* loc) {
				(void)size;
				return loc;
			}
		};

		unsigned char m_space[sizeof(SNode)*N];
		int m_used[N];
	public:
		Node* create() {
			SNode* ret = nullptr;
			
			for (int i = 0; i < N; i++) {		// �����Ƿ��п��пռ�
				if (!m_used[i]) {
					ret = reinterpret_cast<SNode*>(m_space) + i;
					ret = new(ret)SNode();
					m_used[i] = 1;
					break;
				}
			}
			return ret;
		}

		void destory(Node* pn) {
			SNode* space = reinterpret_cast<SNode*>(m_space);
			SNode* psn = dynamic_cast<SNode*>(pn);

			for (int i = 0; i < N; i++) {
				if (pn == (space + i)) {
					m_used[i] = 0;
					psn->~SNode();
					break;			// �����˳�ѭ����Ч�ʸ���һ��
				}
			}
		}
	public:
		StaticLinkList() {
			for (int i = 0; i < N; i++) {
				m_used[i] = 0;
			}
		}

		int capacity() {
			return N;
		}

		~StaticLinkList() {
			this->clear();
		}
	};
}

#endif // !STATICLINKLIST_H_
