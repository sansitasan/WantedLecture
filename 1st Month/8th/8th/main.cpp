#include <iostream>

using namespace std;

template<typename T>
struct Node {
public:
	friend std::ostream&& operator<<(std::ostream& os, const Node<T>& node) {
		os << "Data: " << data << '\n';
		return os;
	}

public:
	Node(T data) : Node(data, nullptr, nullptr) {}

	Node(T data, Node<T>* prev)
		: Node(data, nullptr, prev) {
	}

	Node(T data, Node<T>* next, Node<T>* prev)
		: data(data), prev(prev), next(next) {
	}

	T GetData() const { return data; }
	Node<T>* GetPrev() const { return prev; }
	Node<T>* GetNext() const { return next; }
	void SetPrev(Node<T>* prev) { this->prev = prev; }
	void SetNext(Node<T>* next) { this->next = next; }

private:
	Node<T>* prev;
	Node<T>* next;
	T data;
};

template<typename T>
class LinkedList {
public:
	LinkedList() 
		: count(0) {}

	~LinkedList() {
		Node<T>* current = head;
		Node<T>* deleteNode = nullptr;

		while (current) {
			deleteNode = current;
			current = current->GetNext();

			delete deleteNode;
		}
	}

	void InsertHead(const T& item) {
		++count;
		if (!head) {
			head = new Node<T>(item);
			tail = head;
			return;
		}

		Node<T>* node = new Node<T>(item);
		node->SetNext(head);
		head->SetPrev(node);
		head = node;
	}

	void InsertTail(const T& item) {
		++count;
		if (!head) {
			head = new Node<T>(item);
			tail = head;
			return;
		}
		Node<T>* node = new Node<T>(item, tail);
		tail->SetNext(node);
		tail = node;
	}

	void Insert(const T& item, int index) {
		int idx = count - index < index ? count - index : index;
		bool reverse = idx != index;
		if (!idx) {
			if (reverse) {
				InsertTail(item);
				return;
			}
			InsertHead(item);
			return;
		}

		if (idx < 0) {
			__debugbreak();
		}

		Node<T>* start = reverse ? tail : head;
		Node<T>* trail = nullptr;

		while (idx) {
			trail = reverse ? start->GetPrev() : start->GetNext();
			--idx;

			if (!idx) {
				if (reverse) {
					Node<T>* node = new Node<T>(item, start, trail);
					start->SetPrev(node);
					trail->SetNext(node);
					break;
				}
				Node<T>* node = new Node<T>(item, trail, start);
				trail->SetPrev(node);
				start->SetNext(node);
				break;
			}

			start = trail;
		}
	}

	bool RemoveHead() {
		if (!head) {
			return false;
		}
		--count;

		Node<T>* node = head->GetNext();
		if (!node) { 
			tail = nullptr;
		}
		delete head;
		head = node;
		if (node) {
			node->SetPrev(nullptr);
		}
		return true;
	}

	bool RemoveTail() {
		if (!tail) {
			return false;
		}
		--count;

		Node<T>* node = tail->GetPrev();
		if (!node) {
			delete head;
			head = nullptr;
		}
		delete tail;
		tail = node;
		return true;
	}

	void RemoveIndex(int index) {
		int idx = count - index < index ? count - index : index;
		bool reverse = idx != index;
		if (!idx) {
			if (reverse) {
				RemoveTail();
				return;
			}
			RemoveHead();
			return;
		}

		if (idx < 0) {
			__debugbreak();
		}

		Node<T>* start = reverse ? tail : head;
		Node<T>* trail = nullptr;

		while (idx) {
			trail = reverse ? start->GetPrev() : start->GetNext();
			--idx;

			if (!idx) {
				RemoveNode(trail);
				break;
			}

			start = trail;
		}
	}

	void Remove(const T& item) {
		Node<T>* current = head;

		while (current) {
			if (current->GetData() == item) {
				RemoveNode(current);
			}
			current = current->GetNext();
		}
		std::cout << "해당 값이 없습니다.\n";
	}

	T GetHead() const {
		if (!head) { __debugbreak(); }
		return head->GetData();
	}

	T GetTail() const {
		if (!tail) { __debugbreak(); }
		return tail->GetData();
	}

	int Count() const { return count; }

private:
	Node<T>* head = nullptr;
	Node<T>* tail = nullptr;
	int count;

	//에러 함수 포인터
	using ListEmptyErrorEvent = void (*)();

	void RemoveNode(Node<T>* current) {
		if (head == tail) {
			delete head;
			head = tail = nullptr;
			return;
		}

		if (current == head) {
			current = current->GetNext();
			delete head;
			current->SetPrev(nullptr);
			head = current;
			return;
		}

		if (current == tail) {
			current = current->GetPrev();
			delete tail;
			current->SetNext(nullptr);
			tail = current;
			return;
		}

		current->GetNext()->SetPrev(current->GetPrev());
		current->GetPrev()->SetNext(current->GetNext());
		delete current;
		return;
	}
};

int main() {
	LinkedList<int> ll;
	ll.InsertTail(10);
	ll.InsertTail(12);
	ll.InsertHead(9);
	ll.Insert(11, 2);

	ll.Remove(10);
	ll.Remove(9);
	ll.Remove(11);

	return 0;
}