#pragma once
#include <set>
#include <map>
#include<string>
using namespace std;
class SymbolSetAndPriority
{
public:
	static set<string> ops; //定义符号集合
	static map<string, int>priority;//定义符号优先级字典

	SymbolSetAndPriority();
};

