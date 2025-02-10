/*
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
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>

using namespace std;

vector<vector<int>> visit;
vector<vector<short>> result;
vector<int> regionType;

short dx[4] = { 1, -1, 0 ,0 };
short dy[4] = { 0, 0, 1, -1 };

void BFS(const pair<short, short>& coord, short N, short M, int num) {
	int count = 0;
	queue<pair<short, short>> q;
	q.push(coord);
	pair<short, short> curCoord;

	while (!q.empty()) {
		++count;
		curCoord = q.front();
		q.pop();

		visit[curCoord.first][curCoord.second] = num;
		for (short i = 0; i < 4; ++i) {
			if (curCoord.first + dx[i] < 0 || curCoord.first + dx[i] > N - 1) continue;
			if (curCoord.second + dy[i] < 0 || curCoord.second + dy[i] > M - 1) continue;
			if (visit[curCoord.first + dx[i]][curCoord.second + dy[i]]) continue;
			q.push(make_pair(curCoord.first + dx[i], curCoord.second + dy[i]));
		}
	}

	count %= 10;
	regionType[num] = count;
}

int main() {
	ios_base::sync_with_stdio(false);
	cout.tie(NULL);
	cin.tie(NULL);
	short N, M, temp;
	string str;

	cin >> N >> M;
	queue<pair<short, short>> wall;
	queue<pair<short, short>> empty;
	visit.assign(N, vector<int>(M, 0));
	result.assign(N, vector<short>(M, 0));

	pair<short, short> front;

	for (short i = 0; i < N; ++i) {
		cin >> str;
		for (short j = 0; j < M; ++j) {
			temp = str[j] - '0';
			if (temp) {
				wall.push(make_pair(i, j));
				visit[i][j] = -1;
				continue;
			}

			empty.push(make_pair(i, j));
		}
	}

	temp = 1;

	while (!empty.empty()) {
		front = empty.front();
		empty.pop();

		if (visit[front.first][front.second]) continue;
		regionType.push_back(0);
		BFS(front, N, M, regionType.size());
	}
	vector<bool> check(regionType.size(), 0);
	short x, y;

	while (!wall.empty()) {
		check.clear();
		temp = 1;
		front = wall.front();
		wall.pop();
		for (int i = 0; i < 4; ++i) {
			x = front.first + dx[i];
			y = front.second + dy[i];

			if (x < 0 || x > N - 1) continue;
			if (y < 0 || y > M - 1) continue;
			if (check[visit[x][y]]) continue;
			check[visit[x][y]] = 1;
			temp += regionType[visit[x][y]];
		}
		result[front.first][front.second] = temp % 10;
		check.clear();
	}

	for (short i = 0; i < N; ++i) {
		for (short j = 0; j < M; ++j) {
			cout << result[i][j];
		}
		cout << '\n';
	}

	return 0;
}