#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

#pragma region Test
// 유저 정보
struct UserInfo
{
	UserInfo() = default;
	UserInfo(const char* name, int level, int exp) 
		: userName(name), level(level), exp(exp) { }

	string userName; // 이름
	int level; // 레벨
	int exp; // 경험치
};

// 게임 방의 유저를 관리하는 클래스
// 방에는 최대 6명까지 들어 갈 수 있다.
// 방에 들어 오는 순서 중 가장 먼저 들어 온 사람이 방장이 된다.
class GameRoomUser
{
public:
	GameRoomUser() {
	}

	~GameRoomUser() {
		Clear();
	}

	// 방에 유저 추가
	bool AddUser(UserInfo& userInfo) {
		if (users.size() == 6) return false;

		if (users.empty()) masterUserName = userInfo.userName;

		users.push_back(userInfo);
		return true;
	}

	// 방에서 유저 삭제.
	// 만약 방장이 나가면 userName에 새로운 방장의 이름을 설정 해야 된다.
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

	// 방에 유저가 없는지 확인. 없으면 true 반환
	bool IsEmpty() {
		return users.empty();
	}

	// 방에 유저가 꽉 찼는지 확인. 꽉 찼다면 true 반환
	bool IsFull() {
		return users.capacity() == users.size();
	}

	// 특정 유저의 정보
	UserInfo& GetUserOfName(const char* userName) {
		for (int i = 0; i < static_cast<int>(users.size()); ++i) {
			if (strcmp(users[i].userName.c_str(), userName)) continue;
			return users[i];
		}

		assert(0);
	}

	// 방장의 유저 정보
	UserInfo& GetMasterUser() {
		return GetUserOfName(masterUserName.c_str());
	}

	// 가장 마지막에 방에 들어 온 유저의 정보
	UserInfo& GetUserOfLastOrder() {
		if (users.empty()) {
			assert(0);
		}
		return users[users.size() - 1];
	}

	// 특정 순서에 들어 온 유저를 쫒아낸다.
	bool BanUser(int orderNum) {
		if (users.size() < orderNum) {
			return false;
		}

		if (orderNum == 1) {
			DeleteUser(users[orderNum - 1].userName.c_str());
		}

		return true;
	}

	// 모든 유저를 삭제한다.
	void Clear() {
		masterUserName.clear();
		users.clear();
	}

private:
	vector<UserInfo> users;
	string masterUserName; // 방장의 이름
};

ostream& operator<<(ostream& os, UserInfo& userInfo)
{
	return os << "UserName: " << userInfo.userName
		<< ", Level: " << userInfo.level << ", Exp: " << userInfo.exp << endl;
}
#pragma endregion


int main() {
	// 방 생성.
	GameRoomUser gameRoom;

	// 유저 추가.
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

	// 방장 확인.
	UserInfo roomMaster = gameRoom.GetMasterUser();
	if (roomMaster.userName != "")
	{
		cout << "방장은 " << roomMaster.userName << " 입니다.\n";
	}

	// 방장 밴.
	gameRoom.BanUser(1);

	// 3번 밴.
	gameRoom.BanUser(3);

	// GameDev의 레벨 확인.
	cout << "[TaeJun의 정보] " << gameRoom.GetUserOfName("TaeJun");

	// 마지막에 방에 들어온 유저 정보.
	cout << "[가장 마지막에 들어온 유저 정보] " << gameRoom.GetUserOfLastOrder();

	// 모든 유저 삭제.
	gameRoom.Clear();

	// 모든 유저 삭제 후 비었는지 확인.
	cout << (gameRoom.IsEmpty() == true ? "방이 비었습니다.\n" : "방이 비어있지 않습니다\n");
	//vector<int> vec;
	//
	//for (int i = 0; i < 1000; ++i) {
	//	vec.emplace_back(i);
	//}

	//vec.clear();

	//크기 조정
	//capacity를 줄이는 것이 아닌 size를 줄이는 것
	//vec.resize(100);
	//공간 확보
	//재할당 방지 목적
	//따라서 공간 줄이기는 안 된다
	//vec.reserve(50);

	//메모리 확보
	//크기에 맞게 줄이기
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