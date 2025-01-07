#include <iostream>

template<typename T>
struct Node {
public:
	friend std::ostream&& operator<<(std::ostream& os, const Node<T>& node) {
		os << "Data: " << data << '\n';
		return os;
	}

public:
	Node() {
		prev = nullptr;
		next = nullptr;
		data = '\0';
	}

	Node(T data) : Node(data, nullptr, nullptr) {}

	Node(T data, Node<T>* prev)
		: Node(data, nullptr, prev) {
	}

	Node(T data, Node<T>* prev, Node<T>* next)
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
	//에러 함수 포인터
	using ListEmptyErrorEvent = void (*)();

	using Comparer = bool (*)(T& left, T& right);
public:
	LinkedList()
		: count(0), head(new Node<T>()), tail(new Node<T>()) {
		head->SetNext(tail);
		tail->SetPrev(head);
	}

	LinkedList(ListEmptyErrorEvent errorHandler)
		:LinkedList<T>()
	{
		errorEvent = errorHandler;
	}

	~LinkedList() {

		Clear();

		delete head;
		delete tail;
	}

	void Clear() {

		if (!count) {
			RaiseEmptyErrorEvent();
			return;
		}

		Node<T>* current = head->GetNext();

		while (current != tail) {
			Node<T>* next = current->GetNext();
			delete current;
			current = next;
		}

		count = 0;
		head->SetNext(tail);
		tail->SetPrev(head);
	}

	//리스트가 비었을 때 오류 이벤트를 발생시키는 함수
	void RaiseEmptyErrorEvent() {
		if (errorEvent) {
			errorEvent();
		}
	}

	void AddToFirst(const T& item) {
		Node<T>* newNode = new Node<T>(item, head, head->GetNext());
		head->GetNext()->SetPrev(newNode);
		head->SetNext(newNode);

		++count;
	}

	void AddToLast(const T& item) {
		Node<T>* newNode = new Node<T>(item, tail->GetPrev(), tail);
		tail->GetPrev()->SetNext(newNode);
		tail->SetPrev(newNode);

		++count;
	}

	void Insert(const T& item, int index) {

	}

	void Delete(const T& item, Comparer comparer = nullptr) {
		if (!count) {
			RaiseEmptyErrorEvent();
			return;
		}

		Node<T>* deleteNode = head->GetNext();

		while (deleteNode != tail) {
			if (deleteNode->GetData() == item) {
				break;
			}

			deleteNode = deleteNode->GetNext();
		}

		if (deleteNode == tail) {
			RaiseEmptyErrorEvent();
			return;
		}

		deleteNode->GetNext()->SetPrev(deleteNode->GetPrev());
		deleteNode->GetPrev()->SetNext(deleteNode->GetNext());

		delete deleteNode;
		--count;
	}

	bool Find(const T& item, Node<T>* outNode) {
		outNode = Find(item);
		return outNode != nullptr;
	}

	Node<T>* Find(const T& item) {
		Node<T>* current = head->GetNext();

		while (current != tail) {
			if (current->GetData() == item) {
				return current;
			}
			current = current->GetNext();
		}

		return nullptr;
	}

	void Print() {
		Node<T>* current = head->GetNext();

		while (current != tail) {
			std::cout << "Data: " << current->GetData() << '\n';
			current = current->GetNext();
		}
	}

	int Count() const { return count; }

private:
	Node<T>* head = nullptr;
	Node<T>* tail = nullptr;
	int count;

	ListEmptyErrorEvent errorEvent = nullptr;
};

//이벤트 리스너 함수
void OnListEmptyError() {
	std::cout << "데이터가 없읍니다...\n";
	//Do SomeThing
}

int main() {
	LinkedList<int> ll;

	ll.Delete(100);
	ll.Clear();

	ll.AddToFirst(10);
	ll.AddToFirst(20);
	ll.AddToFirst(30);
	ll.AddToFirst(40);
	ll.AddToFirst(50);

	std::cout << "----------list Print-----------\n";
	ll.Print();

	ll.AddToLast(100);
	ll.AddToLast(90);
	ll.AddToLast(80);
	ll.AddToLast(70);
	ll.AddToLast(60);

	std::cout << "----------list Print-----------\n";
	ll.Print();

	ll.Delete(100);
	ll.Delete(30);
	ll.Delete(60);

	std::cout << "----------list Print-----------\n";
	ll.Print();

	return 0;
}