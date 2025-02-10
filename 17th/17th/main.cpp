#include <iostream>

using namespace std;

//class UnCopyable {
//protected:
//	UnCopyable() {};
//	~UnCopyable() {};
//private:
//	UnCopyable(const UnCopyable&);
//	UnCopyable& operator=(const UnCopyable&);
//};

class Test {
public:

protected:
	
};

class HomeForSale : public Test{
public:
	HomeForSale() = default;
	HomeForSale(const HomeForSale&) = delete;
private:
	
};

int main() {

	cin.get();
	return 0;
}