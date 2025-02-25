#pragma once
#include "Document.h"

class IDocumentProcess
{
public:
    virtual void Process(const Document& document) = 0;
};

