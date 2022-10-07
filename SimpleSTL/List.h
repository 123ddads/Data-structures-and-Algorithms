#ifndef _LIST_H_
#define _LIST_H_

#include"Object.h"

namespace DTLib {
	template<typename T>
	class List :public Object {
	protected:
		List(const List&);	// 禁止拷贝构造
		List& operator=(const List&);	// 禁止赋值操作
	public:	
		List(){}	// 因为自己写了构造函数，故不会调用默认构造函数，不然会报错
		virtual bool insert(const T& e) = 0;	// 从尾部插入
		virtual bool insert(int i, const T& e) = 0;		// 指定位置插入
		virtual bool remove(int i) = 0;
		virtual bool set(int i, const T& e) = 0;
		virtual bool get(int i, T& e)const = 0;
		virtual int length()const = 0;
		virtual int find(const T& e)const = 0;	// 查找指定的值是否存在于线性表中
		virtual void clear() = 0;
	};
}


#endif // !_LIST_H_

