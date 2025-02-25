#pragma once
#include <iostream>
#include <queue>
#include <vector>

struct Location {
	Location(int row = 0, int col = 0)
		: row(row), col(col) { }

	int row;
	int col;
};

int mazeSize = 6;
char startMark = 'e';
char destinationMark = 'x';
char wallMark = '1';
char roadMark = '0';

std::vector<std::vector<char>> map =
{
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'}
};

bool IsValid(int row, int col) {
	if (row < 0 || row >= mazeSize || 
		col < 0 || col >= mazeSize) return false;

	return map[row][col] == roadMark || map[row][col] == destinationMark;
}

void FindStartLocation(int& row, int& col) {
	for (int i = 0; i < mazeSize; ++i) {
		for (int j = 0; j < mazeSize; ++j) {
			std::cout << map[i][j] << ' ';
			if (map[i][j] != startMark) continue;

			row = i;
			col = j;
		}
		std::cout << '\n';
	}

	std::cout << '\n';
}

void ReadMap() {
	FILE* file;
	fopen_s(&file, "map.txt", "rb");
	if (!file) return;

	fseek(file, 0, SEEK_END);

	size_t readSize = ftell(file);
	rewind(file);

	char* buffer = new char[readSize + 1];
	char* remainBuffer = nullptr;
	char* token = nullptr;
	size_t bytesRead = fread(buffer, 1, readSize, file);
	if (readSize != bytesRead) return;

	token = strtok_s(buffer, ",", &remainBuffer);
	_snscanf_s(token, strlen(token), "size:%d", &mazeSize);
	token = strtok_s(NULL, ",", &remainBuffer);
	_snscanf_s(token, strlen(token), "start:%c", &startMark, 1);
	token = strtok_s(NULL, ",", &remainBuffer);
	_snscanf_s(token, strlen(token), "destination:%c", &destinationMark, 1);
	int x = 0, y = 0;
	int idx;
	while (token) {
		token = strtok_s(NULL, ",", &remainBuffer);
		idx = 0;
		if (!token) break;
		if (token[0] == '\r') idx += 2;

		map[x][y] = token[idx];
		if (++y != mazeSize) continue;
		++x;
		y = 0;
	}

	delete[] buffer;
}

void EscapeMaze() {
	ReadMap();

	int row = 0, col = 0;
	FindStartLocation(row, col);
	
	std::queue<Location> queue; 
	queue.emplace(Location(row, col));
	
	while (!queue.empty()) {
		Location current = queue.front();
		queue.pop();
	
		row = current.row;
		col = current.col;
	
		std::cout << "Location: (" << row << ", " << col << "), \n";
	
		if (map[row][col] == destinationMark) {
			std::cout << "\n미로 탐색 성공\n";
			return;
		}
	
		map[row][col] = '.';
	
		if (IsValid(row - 1, col)) queue.emplace(Location(row - 1, col));
		if (IsValid(row + 1, col)) queue.emplace(Location(row + 1, col));
		if (IsValid(row, col - 1)) queue.emplace(Location(row, col - 1));
		if (IsValid(row, col + 1)) queue.emplace(Location(row, col + 1));
	}
	
	std::cout << "\n 미로 탐색 실패\n";
};