#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

#pragma region Test
// ���� ����
struct UserInfo
{
	UserInfo() = default;
	UserInfo(const char* name, int level, int exp) 
		: userName(name), level(level), exp(exp) { }

	string userName; // �̸�
	int level; // ����
	int exp; // ����ġ
};

// ���� ���� ������ �����ϴ� Ŭ����
// �濡�� �ִ� 6����� ��� �� �� �ִ�.
// �濡 ��� ���� ���� �� ���� ���� ��� �� ����� ������ �ȴ�.
class GameRoomUser
{
public:
	GameRoomUser() {
	}

	~GameRoomUser() {
		Clear();
	}

	// �濡 ���� �߰�
	bool AddUser(UserInfo& userInfo) {
		if (users.size() == 6) return false;

		if (users.empty()) masterUserName = userInfo.userName;

		users.push_back(userInfo);
		return true;
	}

	// �濡�� ���� ����.
	// ���� ������ ������ userName�� ���ο� ������ �̸��� ���� �ؾ� �ȴ�.
	bool DeleteUser(const char* userName) {
		int idx = -1;
		for (int i = 0; i < static_cast<int>(users.size()); ++i) {
			if (strcmp(users[i].userName.c_str(), userName)) continue;
			idx = i;
			break;
		}

		if (idx == -1) return false;

		users.erase(users.begin() + idx);
		if (users.empty()) {
			masterUserName.clear();
			return true;
		}

		if (!idx) {
			masterUserName = users[0].userName;
		}

		return true;
	}

	// �濡 ������ ������ Ȯ��. ������ true ��ȯ
	bool IsEmpty() {
		return users.empty();
	}

	// �濡 ������ �� á���� Ȯ��. �� á�ٸ� true ��ȯ
	bool IsFull() {
		return users.capacity() == users.size();
	}

	// Ư�� ������ ����
	UserInfo& GetUserOfName(const char* userName) {
		for (int i = 0; i < static_cast<int>(users.size()); ++i) {
			if (strcmp(users[i].userName.c_str(), userName)) continue;
			return users[i];
		}

		assert(0);
	}

	// ������ ���� ����
	UserInfo& GetMasterUser() {
		return GetUserOfName(masterUserName.c_str());
	}

	// ���� �������� �濡 ��� �� ������ ����
	UserInfo& GetUserOfLastOrder() {
		if (users.empty()) {
			assert(0);
		}
		return users[users.size() - 1];
	}

	// Ư�� ������ ��� �� ������ �i�Ƴ���.
	bool BanUser(int orderNum) {
		if (users.size() < orderNum) {
			return false;
		}

		if (orderNum == 1) {
			DeleteUser(users[orderNum - 1].userName.c_str());
		}

		return true;
	}

	// ��� ������ �����Ѵ�.
	void Clear() {
		masterUserName.clear();
		users.clear();
	}

private:
	vector<UserInfo> users;
	string masterUserName; // ������ �̸�
};

ostream& operator<<(ostream& os, UserInfo& userInfo)
{
	return os << "UserName: " << userInfo.userName
		<< ", Level: " << userInfo.level << ", Exp: " << userInfo.exp << endl;
}
#pragma endregion


int main() {
	// �� ����.
	GameRoomUser gameRoom;

	// ���� �߰�.
	UserInfo user1("RonnieJ", 1, 30);
	gameRoom.AddUser(user1);

	UserInfo user2("Hamtol2", 10, 670);
	gameRoom.AddUser(user2);

	UserInfo user3("TaeJun", 5, 250);
	gameRoom.AddUser(user3);

	UserInfo user4("Oops", 32, 1250);
	gameRoom.AddUser(user4);

	UserInfo user5("Gamer", 40, 250);
	gameRoom.AddUser(user5);

	UserInfo user6("GameDev", 80, 3425);
	gameRoom.AddUser(user6);

	UserInfo user7("STL", 23, 890);
	gameRoom.AddUser(user7);

	// ���� Ȯ��.
	UserInfo roomMaster = gameRoom.GetMasterUser();
	if (roomMaster.userName != "")
	{
		cout << "������ " << roomMaster.userName << " �Դϴ�.\n";
	}

	// ���� ��.
	gameRoom.BanUser(1);

	// 3�� ��.
	gameRoom.BanUser(3);

	// GameDev�� ���� Ȯ��.
	cout << "[TaeJun�� ����] " << gameRoom.GetUserOfName("TaeJun");

	// �������� �濡 ���� ���� ����.
	cout << "[���� �������� ���� ���� ����] " << gameRoom.GetUserOfLastOrder();

	// ��� ���� ����.
	gameRoom.Clear();

	// ��� ���� ���� �� ������� Ȯ��.
	cout << (gameRoom.IsEmpty() == true ? "���� ������ϴ�.\n" : "���� ������� �ʽ��ϴ�\n");
	//vector<int> vec;
	//
	//for (int i = 0; i < 1000; ++i) {
	//	vec.emplace_back(i);
	//}

	//vec.clear();

	//ũ�� ����
	//capacity�� ���̴� ���� �ƴ� size�� ���̴� ��
	//vec.resize(100);
	//���� Ȯ��
	//���Ҵ� ���� ����
	//���� ���� ���̱�� �� �ȴ�
	//vec.reserve(50);

	//�޸� Ȯ��
	//ũ�⿡ �°� ���̱�
	//vec.shrink_to_fit();

	//vec.erase(vec.begin() + 100);
	//vec.push_back(-1);
	//if (vec.begin() < vec.end()) {
	//	vec.push_back(10000);
	//}
	//vec.end();

	cin.get();
	return 0;
}