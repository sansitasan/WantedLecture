#pragma once
#include "IDocumentProcess.h"
#include "DocumentProcess.h"


class RepaginateProcess : public IDocumentProcess {
public:
    virtual void Process(const Document& document) override
    {
        DocumentProcess::Repaginate(document);
    }
};