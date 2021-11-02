#pragma once
#include <iostream>
#include <stack>
#include "SymbolSetAndPriority.h"
#include "MidexToPreex.h"
#include "PreexParAndEva.h"
#include "FunctionExpression.h"
#include "CommonStackMethod.h"
#include "CharToString.h"
#include "SuffixFunctionEva.h"
using namespace std;

class CallFunction
{
public:
	double callFunction(string expressionStrng);
};

