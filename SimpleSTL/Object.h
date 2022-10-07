#ifndef _OBJECT_H_
#define _OBJECT_H_

namespace DTLib {
	class Object {
	public:
		void* operator new(size_t size) throw();	// �������������쳣��ȫ
		void operator delete(void* p);
		void* operator new[](size_t size) throw();	// �������׳��κ��쳣�����ú������쳣��ȫ��
		void operator delete[](void* p);
		bool operator == (const Object& obj);
		bool operator != (const Object& obj);
		virtual ~Object() = 0;
	};
}

#endif // !_OBJECT_H_