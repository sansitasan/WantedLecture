#include "DataManager.h"
#include "Engine/Engine.h"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
	mapFolder.clear();
}

std::string DataManager::GetMap(int& outX, int& outY, int level) const
{
	FILE* file = nullptr;
	std::string mapLocation(mapFolder), map;
	mapLocation.append("Map.txt");
	fopen_s(&file, mapLocation.c_str(), "rb");

	if (!file) {
		std::cout << "맵 파일 열기 실패.\n";
		__debugbreak();
		return map;
	}

	fseek(file, 0, SEEK_END);

	size_t readSize = ftell(file);

	rewind(file);

	char* buffer = new char[readSize + 1];
	memset(buffer, 0, readSize + 1);
	size_t bytesRead = fread(buffer, 1, readSize, file);

	if (readSize != bytesRead) {
		std::cout << "읽어온 크기가 다름\n";
		__debugbreak();
	}

	buffer[readSize] = '\0';
	int x = 0, y = 0;

	for (int i = 0; i < readSize; ++i) {
		if (buffer[i] == '\n') {
			x = i;
			y = (int)readSize / (x + 2);
			break;
		}
	}
	int nx = ((x - 1) << 1);
	int ny = (y << 1) + 1;
	std::string temp(nx * ny + 1, '\0');
	for (int i = 0; i < ny; ++i) {
		for (int j = 0; j < nx - 1; ++j) {
			temp[nx * i + j] = buffer[(y > i ? (x + 1) * i : (x + 1) * (ny - 1 - i)) + ((x - 1) > j ? j : (nx - 2) - j)];
		}
		temp[nx * (i + 1) - 1] = '\n';
	}

	outX = nx;
	outY = ny;

	fclose(file);
	return temp;
}
