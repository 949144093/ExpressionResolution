#pragma once
#include <set>
#include <map>
#include<string>
using namespace std;
class SymbolSetAndPriority
{
public:
	static set<string> ops; //������ż���
	static map<string, int>priority;//����������ȼ��ֵ�

	SymbolSetAndPriority();
};

