#pragma once
#include "Pair.h"
#include <vector>
#include <iostream>

template<typename T>
struct Node {

};

template<typename Key, typename Value>
class HashTable {
	using namespace std;
public:
	HashTable() : bucketCount(7)
	{
		table = vector<vector<Pair<Key, Value>>>(bucketCount, vector<Pair<Key, Value>>());
	}

	~HashTable() = default;

	void Add(const Key& key, const Value& value) {
		if ((float)bucketCount / count < maxFactor) {

		}

		int hash = GenerateHash(key) % bucketCount;
		table[hash].push_back(Pair(key, value));
		++count;
	}

	bool Delete(const Key& key) {
		int hash = GenerateHash(key) % bucketCount;
		vector<Pair<Key, Value>& position = table[hash];

		for (int i = 0; i < position.size(); ++i) {
			if (key != position[i].key) continue;
			position.erase(position.begin() + i);
			return true;
		}

		return false;
	}

	bool Find(const Key& key, Value& outvalue) {
		int hash = GenerateHash(key) % bucketCount;
		vector<Pair<Key, Value>& position = table[hash];

		for (int i = 0; i < position.size(); ++i) {
			if (key != position[i].key) continue;
			outvalue = position[i].value;
			
			return true;
		}

		return false;
	}

private:
	int count = 0;
	int bucketCount;
	float maxFactor = 1.0f;
	vector<vector<Pair<Key, Value>>> table;

private:
	template<typename Key>
	int GenerateHash(const Key& key) {
		return reinterpret_cast<int>(&key);
	}
};