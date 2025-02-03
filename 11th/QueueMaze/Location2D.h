#pragma once

class Location2D {
public:
	Location2D(int row = 0, int column = 0)
		: row(row), column(column) {}

public:
	int row = 0;
	int column = 0;
};