#pragma once
#include <iostream>
#include "Document.h"

class DocumentProcess {
public:
	static void SpellCheck(const Document& document) {
		std::cout << "���� ����� �˻� �Ϸ�.\n";
	}

	static void Repaginate(const Document& document) {
		std::cout << "���� ������ �缳�� �Ϸ�.\n";
	}

	static void TranslateIntoFrench(const Document& document) {
		std::cout << "��������� ���� �Ϸ�.\n";
	}
private:
};