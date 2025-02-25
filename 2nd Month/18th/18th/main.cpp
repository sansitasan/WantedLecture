#pragma once
#include "RepaginateProcess.h"
#include "SpellcheckProcess.h"
#include "TranslateIntoFrenchProcess.h"
#include <Memory>

#include "DocumentProcessor.h"

using namespace std;

DocumentProcessor* Configure() {
	DocumentProcessor* processor = new DocumentProcessor();
	processor->AddDocumentProcess(DocumentProcess::TranslateIntoFrench);
	processor->AddDocumentProcess(DocumentProcess::SpellCheck);
	processor->AddDocumentProcess(DocumentProcess::Repaginate);

	return processor;
}

int main() {
	Document doc1("Jake Oh", "2025.02.13", "C++ Programming");
	Document doc2("Scott Meyers", "2006.05.20", "Effective C++");

	//문서 처리자 객체 생성 (팩토리 패턴)
	DocumentProcessor* processor = Configure();

	std::cout << "문서 1 처리\n";
	processor->Process(doc1);
	std::cout << '\n';

	std::cout << "문서 2 처리\n";
	processor->Process(doc2);
	std::cout << '\n';

	char test[] = "Hello Mr My Yesterday";

	char* p;
	char* remain = new char[strlen(test)];
	memset(remain, 0, strlen(test));

	p = strtok_s(test, " ", &remain);
	p = strtok_s(test, " ", &remain);
	p = strtok_s(test, " ", &remain);

	delete[] test;
	delete[] remain;
	delete processor;
	return 0;
}