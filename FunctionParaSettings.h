#pragma once
#include <map>
#include <set>
#include<string>
#include<vector>
using namespace std;
class FunctionParaSettings
{
public:
	static map<string,double> funcValue;//��������ֵ��ѯ�ֵ�
	static map<string, int>FuncitonPara;//���庯�����������ֵ�
	static map<string, vector<double>> StringNameToArray; //������������
	static void AddArray(vector<double> array, string name);
	static void AddAtrr(double attr, string name);
	static void ReplaceAtrr(string attr, string name);
	static map<string, string> SymbolReplace;//��������滻��
	static map<string, string> FindType;//����������Ͳ�ѯ��
};

