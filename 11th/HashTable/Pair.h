#pragma once

template<typename KeyType, typename ValueType>
struct Pair {
public:
	Pair()
		:key(), value() {}

	Pair(KeyType key, ValueType value) 
		:key(key), value(value) {}

	~Pair() {}

	bool operator==(const Pair<KeyType, ValueType>& other) {
		return key == other.key && value == other.value;
	}

	bool operator=!(const Pair<KeyType, ValueType>& other) {
		return key != other.key || value != other.value;
	}

public:
	KeyType key;
	ValueType value;
};