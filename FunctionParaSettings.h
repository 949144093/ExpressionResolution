#pragma once
#include <map>
#include <set>
#include<string>
#include<vector>
using namespace std;
class FunctionParaSettings
{
public:
	static map<string,double> funcValue;//定义属性值查询字典
	static map<string, int>FuncitonPara;//定义函数参数个数字典
	static map<string, vector<double>> StringNameToArray; //定义数组存放类
	static void AddArray(vector<double> array, string name);
	static void AddAtrr(double attr, string name);
	static void ReplaceAtrr(string attr, string name);
	static map<string, string> SymbolReplace;//定义符号替换类
	static map<string, string> FindType;//定义参数类型查询类
};

