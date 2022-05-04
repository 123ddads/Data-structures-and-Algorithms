#include <iostream>
#include<string>
#include"Exception.h"

using namespace std;
using namespace DTlib;

int main(int argc, char* argv[]) {
	try {
		THROW_EXCEPTION(ArithmeticException, "test");
	}
	catch (const ArithmeticException& e) {	//由于赋值兼容性原则，子类放在上面
		cout << "catch (const ArithmeticException& e)" << endl;
		cout << e.message() << endl;
		cout << e.location() << endl;
	}
	catch (const Exception& e) {
		cout << "catch (const Exception& e)" << endl;
		cout << e.message() << endl;
		cout << e.location() << endl;
	}

	return 0;
}