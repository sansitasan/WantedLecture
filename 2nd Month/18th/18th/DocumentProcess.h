#pragma once
#include <iostream>
#include "Document.h"

class DocumentProcess {
public:
	static void SpellCheck(const Document& document) {
		std::cout << "문서 맞춤법 검사 완료.\n";
	}

	static void Repaginate(const Document& document) {
		std::cout << "문서 페이지 재설정 완료.\n";
	}

	static void TranslateIntoFrench(const Document& document) {
		std::cout << "프랑스어로 번역 완료.\n";
	}
private:
};