#include <iostream>

using namespace std;

int main() {
	//char buffer[1024];
	//const char* stringValue = "id: 10 name: Sansei balance: 100000";
	//
	//int id, balance;
	//char name[256];
	//
	//sscanf_s(stringValue, "id: %d name: %s balance: %d", &id, name, 256, &balance);
	//
	//cout << "id: " << id << " name: " << name << " balance: " << balance << '\n';
	//ILE* file = nullptr;
	//open_s(&file, "Test.txt", "r+t");
	//
	//f (file) {
	//	fseek(file, 8, SEEK_SET);
	//
	//	char buffer[256];
	//
	//	while (!feof(file)) {
	//		fgets(buffer, 256, file);
	//
	//		cout << buffer;
	//	}
	//
	//	fclose(file);
	//

	int x = 10;
	int* p = new int[10] {};
	int& r = *p;

	delete[] p;

	return 0;
}