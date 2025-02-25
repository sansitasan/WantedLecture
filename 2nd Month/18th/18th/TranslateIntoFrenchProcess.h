#pragma once
#include "IDocumentProcess.h"
#include "DocumentProcess.h"

class TranslateIntoFrenchProcess : public IDocumentProcess
{
public:
    virtual void Process(const Document& document) override
    {
        DocumentProcess::TranslateIntoFrench(document);
    }
};