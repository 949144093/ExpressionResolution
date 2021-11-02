#include "FunctionParaSettings.h"
#include<vector>
map<string, double>FunctionParaSettings::funcValue = 
{
	{"true",1},{"false",0},
	{"True",1},{"False",0}
};
//定义函数参数个数字典
map<string, int>FunctionParaSettings::FuncitonPara = 
{ 
	{"MAX()",2},{"MIN()",2},{"RANDOM()",2},{"SIN()",1},{"COS()",1},{"TAN()",1},{"ASIN()",1},{"ACOS()",1},{"ATAN()",1},{"ATANT()",2},{"SQRT()",1},{"POW()",2},{"ABS()",1},{"INT()",1},{"LOG()",1},{"SUM()",2},{"ift()",3},
	{"max()",2},{"min()",2},{"random()",2},{"sin()",1},{"cos()",1},{"tan()",1},{"asin()",1},{"acos()",1},{"atan()",1},{"atant()",2},{"sqrt()",1},{"pow()",2},{"abs()",1},{"int()",1},{"log()",1},{"sum()",2},{"IFT()",3}
};
map<string, vector<double>> FunctionParaSettings::StringNameToArray = {};
map<string, string>FunctionParaSettings::SymbolReplace = {};
//定义函数 属性类型名查询字典
map<string, string>FunctionParaSettings::FindType =
{
	{"SUM","Function"},
	{"MAX","Function"},
	{"MIN","Function"},
	{"SIN","Function"},
	{"COS","Function"},
	{"TAN","Function"},
	{"SQRT","Function"},
	{"POW","Function"},
	{"ift","Function"},
	{"IFT","Function"},
	{"RANDOM","Function"},
	{"ASIN","Function"},
	{"ACOS","Function"},
	{"ATAN","Function"},
	{"ATANT","Function"},
	{"ABS","Function"},
	{"PARAM","Array"},
	{"IPARAM","Array"},
};


void FunctionParaSettings::AddArray(vector<double> array, string name)
{
	StringNameToArray[name] = array;
	FindType[name] = "Array";
}

void FunctionParaSettings::AddAtrr(double attr, string name)
{
	funcValue[name] = attr;
}

void FunctionParaSettings::ReplaceAtrr(string attr, string name)
{
	SymbolReplace[name] = attr;
}
