#pragma once
#include "DocumentProcess.h"
#include "IDocumentProcess.h"
#include <vector>
#include <functional>

// 문서를 처리하는 처리자 클래스.
class DocumentProcessor
{
public:
	void AddDocumentProcess(std::function<void(const Document&)> process) {
		processes.emplace_back(process);
	}

	void Process(const Document& document) {
		for (auto& process : processes) {
			process(document);
		}
	}

private:
	std::vector<std::function<void(const Document&)>> processes;
//public:
//    std::vector<IDocumentProcess*>& GetProcesses() { return processes; }
//
//    void Process(const Document& doc)
//    {
//        for (IDocumentProcess* process : GetProcesses())
//        {
//            process->Process(doc);
//        }
//    }
//
//private:
//    std::vector<IDocumentProcess*> processes;
};