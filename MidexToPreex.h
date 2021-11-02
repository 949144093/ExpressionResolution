#pragma once
#include <iostream>
#include <stack>
#include <sstream>
#include "SymbolSetAndPriority.h"
using namespace std;
class MidexToPreex
{
public:
	stack<string> MiddleexToPrevex(string& midex);
};

