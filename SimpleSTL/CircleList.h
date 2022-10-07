#ifndef CIRCLELIST_H_
#define CIRCLELIST_H_
 
#include"LinkList.h"

// ѭ������
namespace DTLib {
	template<typename T>
	class CircleList :public LinkList<T> {
	protected:
		typedef typename CircleList<T>::Node Node;

		int mod(int i)const {		// ȡ�����		O(1 )
			return (this->m_length == 0) ? 0 : i % (this->m_length);
		}

		Node* last()const {		// O(n)
			return this->Position(this->m_length - 1)->next;
		}

		void last_to_first()const {		// O(n)
			last()->next = this->m_head.next;
		}
	public:
		bool insert(const T& e) {
			return insert(this->m_length, e);
		}

		bool insert(int i, const T& e) {
			bool ret = true;

			i = i % (this->m_length + 1);
			ret = LinkList<T>::insert(i, e);		// ����0������λ�ò�ֵ, O(n)

			if (ret && (i == 0)) {		// 0��λ�ò�ֵ
				last_to_first();
			}

			return ret;
		}

		bool remove(int i) {		// O(n)
			bool ret = true;
			i = mod(i);
			if (i == 0) {
				Node* toDel = this->m_head.next;

				if (toDel != nullptr) {
					this->m_head.next = toDel->next;
					this->m_length--;

					if (this->m_length > 0) {
						last_to_first();
						if (this->m_current == toDel) {
							this->m_current = toDel->next;
						}
					}
					else {
						this->m_head.next = nullptr;
						this->m_current = nullptr;
					}

					this->destory(toDel);		// Ϊ���쳣��ȫ
				}
				else {
					ret = false;
				}
			}
			else {
				ret = LinkList<T>::remove(i);
			}
			return ret;
		}

		bool set(int i, const T& e) {		// O(n)
			return LinkList<T>::set(mod(i), e);
		}

		T get(int i)const {
			return LinkList<T>::get(mod(i));
		}

		T get(int i, const T& e) {
			return LinkList<T>::get(mod(i), e);
		}

		int find(const T& e)const {			// ����ʵ�ֲ��Ҳ���, O(n)
			int ret = -1;
			Node* slider = this->m_head.next;
			
			for (int i = 0; i < this->m_length; i++) {
				if (slider->value == e) {
					ret = i;
					break;
				}

				slider = slider->next;
			}

			return ret;
		}

		void clear() {			// O(n)
			while (this->m_length > 1) {		// O(n)
				remove(1);		// Ϊ�����Ч�ʣ�ÿ��ɾ���׽ڵ����һ���ڵ㣬ȥ��remove��ʵ��, O(1)
			}
			
			if (this->m_length == 1) {
				Node* toDel = this->m_head.next;

				this->m_head.next = nullptr;
				this->m_length = 0;
				this->m_current = nullptr;

				this->destory(toDel);
			}
		}

		bool move(int i, int step) {		// O(n)
			return LinkList<T>::move(mod(i), step);
		}

		bool end() {		// O(1)
			return (this->m_length == 0) || (this->m_current == nullptr);
		}

		~CircleList() {		// O(n) 
			clear();
		}

	};
}

#endif // !CIRCLELIST_H_