#pragma once

#include "IDocumentProcess.h"
#include "DocumentProcess.h"

class SpellcheckProcess : public IDocumentProcess
{
public:
    virtual void Process(const Document& document) override
    {
        DocumentProcess::SpellCheck(document);
    }
};