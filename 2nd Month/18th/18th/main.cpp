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

	//���� ó���� ��ü ���� (���丮 ����)
	DocumentProcessor* processor = Configure();

	std::cout << "���� 1 ó��\n";
	processor->Process(doc1);
	std::cout << '\n';

	std::cout << "���� 2 ó��\n";
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