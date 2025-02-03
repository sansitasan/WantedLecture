#pragma once
#include "core.h"

class DataManager {
public:
	DataManager();
	~DataManager();

	std::string GetMap(int& outX, int& outY, int level = 0) const;

private:
	std::string mapFolder = "Assets/Maps/";
	std::vector<std::string> mapList;
};