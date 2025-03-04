#include <iostream>
//#include "RedBlackTree.h"
//#include "AStar.h"
#include <Windows.h>
#include <xmmintrin.h>
#include <intrin.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <memory>
#include "MemoryPool.h"
#include <string>
#include <chrono>
#include <vector>

using namespace std;
//using namespace San;

std::vector<std::vector<int>> grid =
{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 1 },
	{ 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
	{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
	{ 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

//enum ECommand {
//	None,
//	Insert,
//	Delete,
//	Find,
//	Print,
//	Quit
//};
//
//inline void ClearScreen() {
//	system("cls");
//}
//
//void ProcessCommandInput(int& commandInput)
//{
//	char inputBuffer[100] = {};
//
//	while (true) {
//		cout << "명령 숫자 입력\n";
//		cout << "1. 노드 추가\n2. 노드 삭제\n3. 노드 검색\n4. 노드 출력\n5. 종료\n";
//		cin >> inputBuffer;
//
//		if (commandInput = atoi(inputBuffer)) {
//			if (commandInput <= ECommand::None || commandInput > ECommand::Quit) {
//				ClearScreen();
//				cout << "오류: 명령은 1부터 5까지만 입력 가능합니다.\n";
//				continue;
//			}
//
//			break;
//		}
//
//		ClearScreen();
//		cout << "오류: 명령은 숫자만 입력 가능합니다.\n";
//	}
//}
//
//void ProcessParamInput(int& param) {
//	char inputBuffer[100] = {};
//	while (true) {
//		cout << "파라미터를 입력하세요(1-200)\n";
//		cin >> inputBuffer;
//
//		if (param = atoi(inputBuffer)) {
//			if (param > 200) {
//				ClearScreen();
//				cout << "오류: 파라미터는 1부터 200까지만 입력 가능합니다.\n";
//				continue;
//			}
//			break;
//		}
//
//		ClearScreen();
//		cout << "오류: 파라미터는 숫자만 입력 가능합니다.\n";
//	}
//}
//
//void ProcessCommand(int param, RedBlackTree<int>& tree) {
//	ECommand command = (ECommand)param;
//
//	if (command == ECommand::Print) {
//		tree.Print();
//		return;
//	}
//
//	else if (command == ECommand::Quit) {
//		return;
//	}
//
//	ProcessParamInput(param);
//	ClearScreen();
//	switch (command) {
//	case ECommand::Insert:
//		tree.Insert(param);
//		break;
//
//	case ECommand::Delete:
//		tree.Remove(param);
//		break;
//
//	case ECommand::Find:
//		Node<int>* result = nullptr;
//		if (!tree.Find(param, &result)) {
//			cout << "노드를 찾지 못했습니다. (검색 값: " << param << " )\n";
//			return;
//		}
//
//		result->IsBlack() ? SetTextColor(ETextColor::BrightWhite) : SetTextColor(ETextColor::Red);
//		cout << "검색된 노드: " << result->Data() << " (Color: " << result->ColorString() << ")\n";
//		SetTextColor(ETextColor::White);
//
//		break;
//	}
//}

// alignas(16)
//CPU 친화적
//x86계열은 16바이트씩 읽을 수 있다.

struct SIMDVec2 {
public:
	inline SIMDVec2() : value({}) {}
	inline SIMDVec2(float x, float y) : value(MM128Union(x, y)) {}
	inline SIMDVec2(int x, int y) : value(MM128Union(x, y)) {}
	inline SIMDVec2(__m128 value) : value(value) {}

	inline SIMDVec2 operator/(const float other) {
		return SIMDVec2(_mm_div_ps(value.val, _mm_set_ps1(other)));
	}

private:
	union MM128Union {
		__m128 val;
		float fval[2];
		int ival[2];
		MM128Union(__m128 val) : val(val) {}
		MM128Union(float x, float y) : fval{ x, y } {}
		MM128Union(int x, int y) : ival{ x, y } {}
	};

	MM128Union value;
};

struct Vector2 {
public:
	inline Vector2() : x(0), y(0) {}
	inline Vector2(float x, float y) : x(x), y(y) {}
	inline Vector2(int x, int y) : x(x), y(y) {}
	
	inline Vector2 operator/(const float other) {
		return Vector2(x / other, y / other);
	}

private:
	float x;
	float y;
};

void CompareTest() {
	unsigned long long avera = 0, averb = 0;
	for (int j = 0; j < 1; ++j) {
		SIMDVec2 a(_mm_setzero_ps());
		SIMDVec2 b(_mm_setzero_ps());
		SIMDVec2 c;

		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 100000000; ++i) {
			c = a / 3;
		}
		auto end = std::chrono::high_resolution_clock::now();
		;avera += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

		Vector2 d;
		Vector2 e;
		Vector2 f;

		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 100000000; ++i) {
			d = e / 3;
		}
		end = std::chrono::high_resolution_clock::now();
		averb += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	}

	std::cout << "SIMD __m128 Divide average: "
		<< avera * 0.01f << '\n';

	std::cout << "Normal Verctor Divide average: "
		<< averb * 0.01f << '\n';
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(195);




	/*
	Node* startNode = nullptr;
	Node* goalNode = nullptr;
	bool initialized = false;

	AStar* aStar = new AStar();
	vector<Node*> path;
	aStar->DisplayGridWithPath(grid, path);
	cout << '\n';

	for (int y = 0; y < (int)grid.size(); ++y) {
		if (startNode && goalNode) {
			initialized = true;
			break;
		}

		for (int x = 0; x < (int)grid[y].size(); ++x) {
			if (startNode && goalNode) break;

			if (!grid[y][x] || grid[y][x] == 1) continue;

			if (grid[y][x] == 2) {
				startNode = new Node(x, y);
				grid[y][x] = 0;
				continue;
			}

			else if (grid[y][x] == 3) {
				goalNode = new Node(x, y);
				grid[y][x] = 0;
				continue;
			}
		}
	}

	if (aStar->FindPath(startNode, goalNode, grid, &path)) {
		cout << "경로 탐색 성공! 탐색 경로: \n";
		for (Node* node : path) {
			cout << "(" << node->position.x << ", " << node->position.y << ") -> ";
		}
		cout << "도착!\n";

		cout << "경로를 맵에 표시한 결과: \n";
		aStar->DisplayGridWithPath(grid, path);
	}

	else {
		cout << "경로 탐색 실패...\n";
	}
	SafeDelete(aStar);
	SafeDelete(goalNode);
	*/
	_CrtDumpMemoryLeaks();
	return 0;
}