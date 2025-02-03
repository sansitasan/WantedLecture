#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

struct Item {
	Item(int code = 0, int price = 0)
		: code(code), price(price) { }

	int code;
	int price;
};

ostream& operator<<(ostream& os, const Item& item) {
	return os << "코드: " << item.code << ", 가격: " << item.price << '\n';
}

struct Compare {
	bool operator()(const Item& a, const Item& b) {
		if (a.code == b.code) return a.price < b.price;
		return a.code < b.code;
	}
};

int main() {
	list<Item> itemList;
	itemList.emplace_front(Item(5, 2000));
	itemList.emplace_front(Item(6, 10000));
	itemList.emplace_back(Item(7, 4000));
	itemList.emplace_back(Item(8, 8000));
	itemList.emplace_front(Item(2, 200));
	itemList.emplace_front(Item(1, 1000));
	itemList.emplace_back(Item(3, 400));
	itemList.emplace_back(Item(4, 800));

	for (auto it = itemList.begin(); it != itemList.end(); ++it) {
		cout << *it;
	}
	Compare comparer;
	itemList.sort(comparer);

	cout << '\n';
	for (auto it = itemList.begin(); it != itemList.end(); ++it) {
		cout << *it;
	}

	//리턴형을 ->로 알려줄 수 있음
	itemList.sort([](const Item& left, const Item& right) -> bool {
		if (left.code == right.code) return left.price > right.price;
		return left.code > right.code;
		});

	cout << "\n역순정렬\n";
	for (auto it = itemList.begin(); it != itemList.end(); ++it) {
		cout << *it;
	}

	//랜덤엑세스가 안 되면 사용 불가
	//인덱스 접근이 안 되면 사용 불가
	//sort(itemList.begin(), itemList.end(), comparer);

	cin.get();
	return 0;
}