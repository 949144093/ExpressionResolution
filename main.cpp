// expressionResolution.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <iostream>
#include <stack>
#include <map>
#include <algorithm>
#include "SymbolSetAndPriority.h"
#include "MidexToPreex.h"
#include "PreexParAndEva.h"
#include "FunctionExpression.h"
#include "CommonStackMethod.h"
#include "CharToString.h"
#include "CallFunction.h"
#include "SuffixFunctionEva.h"
#include "FunctionParaSettings.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
using namespace std;



//函数的main入口，进行调用方法，测试方法等等
int main() {
	//cout << atan2(5.0,2.0)*180/M_PI;
	double a[10] = { 9,2,3,4.78,5,6,7,8,9,10 };
	double b[10] = { 10,20,30,40,50,60,70,80,90,100 };
	double c[10] = { 100,200,300,400,500,600,700,800,900,1000 };
	double d[5] = { 54,51,25,42,53 };
	double func1 = -50;
	double func2 = 10;
	double func = 20;
	double OutBore = 50.2;
	double RodBore = 70;
	char G = 'G';


	double oldPARA[10] = {60,200,200,200,65,4,3,2,1,0};
	double PARAM[10] = {200,8,7,6,5,4,8,2,1,0};
	double IPARAM[10] = {9,8,7,6,5,4,3,2,1,0};
	double OPAR[10] = {1,3,5,7,9,11,13,15,17,19};
	double ODESP[10] = {2,4,6,8,10,12,14,16,18,20};
	double ADESP[10] = {1,1,1,1,1,1,1,1,1,1};
	double DESP[10] = {2,2,2,2,2,2,2,2,2,2};
	double APAR[10] = {3,3,3,3,3,3,3,3,3,3};
	//传参数组和数组名(string类型)

	vector<double>PARA(oldPARA,oldPARA+10);
	vector<double>PARA1(PARAM, PARAM +10);

	/*FunctionParaSettings::AddArray(a, "a");
	FunctionParaSettings::AddArray(b, "b");
	FunctionParaSettings::AddArray(c, "c");
	FunctionParaSettings::AddArray(d, "d");*/
	FunctionParaSettings::AddArray(PARA, "SuppParas");
	FunctionParaSettings::AddArray(PARA1, "Part_2_Paras");
	//FunctionParaSettings::AddArray(PARAM, "PARAM");
	//FunctionParaSettings::AddArray(IPARAM, "IPARAM");
	//FunctionParaSettings::AddArray(OPAR, "OPAR");
	//FunctionParaSettings::AddArray(ODESP, "ODESP");
	//FunctionParaSettings::AddArray(ADESP, "ADESP");
	//FunctionParaSettings::AddArray(DESP, "DESP");
	//FunctionParaSettings::AddArray(APAR, "APAR");

	FunctionParaSettings::AddAtrr(func1, "func1");
	FunctionParaSettings::AddAtrr(func2, "func2");
	FunctionParaSettings::AddAtrr(func, "func");
	FunctionParaSettings::AddAtrr(OutBore, "OutBore");
	FunctionParaSettings::AddAtrr(RodBore, "RodBore");
	FunctionParaSettings::AddAtrr(G, "G");
	FunctionParaSettings::AddAtrr(M_PI, "PI");
	FunctionParaSettings::AddAtrr(M_E, "e");

	FunctionParaSettings::ReplaceAtrr("*","TIMES");
	FunctionParaSettings::ReplaceAtrr("/","DIV");
	FunctionParaSettings::ReplaceAtrr("+","ADD");
	FunctionParaSettings::ReplaceAtrr("-","SUB");

	CallFunction CF;


	cout << CF.callFunction("max(int((OutBore+20)/2),40)")<<endl;


	/*
	测试数据 
	1+(2+3)*4-5
	1.7+(2+4.3)*4.7-502
	1.7 + ( 2+ 4.3 ) * 4.7 - 502
	(1>2)+(2+(3<5))*4-5%2
	(1>2)+(2+(3<=5))*4-5%2+(1!=2)+2==14
	MAX(ABS(RANDOM(-90, -10)), RANDOM(1, 9))
	MAX(ABS(RANDOM(func1, -10)), RANDOM(1, func2))
	MAX(ABS(RANDOM(-10,a[3])), RANDOM(1, func2))
	a[3]
	func1
	a[3]+func1+50
	支持常见异常输入处理
	中文字符
	多余括号
	直接回车
	无效空格
	sss
	aaa
	bbb

	支持
	-2+3+4
	-2+-3+4
	1+MAX(ABS(RANDOM(-10,a[3])), RANDOM(1, func2))+a[3]
	(PARA[1]/2)
	(PARA[1]/2-PARA[4]-(PARA[2]/2-PARA[3]/2)*TAN(8))
	(OPAR[4]*COS(30))
	(-OPAR[1]/2+APAR[4]+DESP[6])
	(ODESP[1]/2-ADESP[1])

	SUM PARAM 4 IPARAM 1
	1 times 3 add 5
	SUM SUM PARAM 4 IPARAM 1 5
	SUM IPARAM 1 PARAM 6 TIMES SUM 50 60 ADD 1 DIV SUM SUM 2 3 50
	( RPRO OFFS * -1 )

	exit()
	cls()

	*/


	////实现基础一位整数基础加减乘除中缀转前缀
	//cout << "实现基础一位整数加减乘除中缀转前缀以及计算"<<endl;
	//string a = "1+(2+3)*4-5";
	//cout << "中缀表达式为:" << a << endl;
	//cout << "对应前缀表达式为:";
	//stack<string> s1 = M.MiddleexToPrevex(a);
	//C.PutStack(s1);//- + 1 * + 2 3 4 5
	//P.Cal_Preex(s1);
	//cout << "\n-------------------------\n";

	////实现基础多位整数基础加减乘除中缀转前缀并支持包含空格
	//cout << "实现多位整数基础加减乘除中缀转前缀并支持包含空格" << endl;
	//string b = "1 + ( 2 + 301 ) * 4 - 5";
	//cout << "中缀表达式为:" << b << endl;
	//cout << "对应前缀表达式为:";
	//stack<string> s2 = M.MiddleexToPrevex(b);
	//C.PutStack(s2);//- + 1 * + 2 301 4 5
	//P.Cal_Preex(s2);
	//cout << "\n-------------------------\n";

	////实现包含小数基础加减乘除中缀转前缀
	//cout << "实现包含小数基础加减乘除中缀转前缀" << endl;
	//string c = "1.7+(2+4.3)*4.7-502";
	//cout << "中缀表达式为:" << c << endl;
	//cout << "对应前缀表达式为:";
	//stack<string> s3 = M.MiddleexToPrevex(c);
	//C.PutStack(s3);//- + 1.7 * + 2 4.3 4.7 502
	//P.Cal_Preex(s3);
	//cout << "\n-------------------------\n";

	////实现支持函数解析中缀转后缀 参数仅支持整数
	//cout << "希望实现支持函数解析中缀转后缀 参数仅支持整数" << endl;
	//string d = "max(abs(RANDOM(-90,-10)),RANDOM(1,9))";
	//cout << "中缀表达式为:" << d << endl;
	//cout << "对应后缀表达式为:";
	//stack<string> s4 = F.FuncExpression(d);
	//C.PutStack(s4);
	//cout << "-------------------------\n";
	////需要输出声明函数后缀表达式  total_house = eval(response.xpath('//*[@id="beike"]/div[1]/div[4]/div[1]/div[2]/div[1]/h2/span/text()').extract()[0])

	////实现支持函数解析中缀转后缀 参数支持属性
	//cout << "实现支持函数解析中缀转后缀 参数支持属性" << endl;
	//string e = "max(abs(RANDOM(func1,-10)),RANDOM(1,func2))";
	//cout << "中缀表达式为:" << e << endl;
	//cout << "对应后缀表达式为:";
	//stack<string> s5 = F.FuncExpression(e);
	//C.PutStack(s5);
	//cout << "-------------------------\n";
	////需要输出声明函数后缀表达式 func1 -10 RANDOM () abs () 1 func2 RANDOM () max ()

	////增加了取余计算,逻辑大于，逻辑小于，记得加上括号，否则会出现异常结果
	//cout << "增加了取余计算,逻辑大于，逻辑小于，逻辑运算需加上括号，否则最后执行逻辑运算返回True或者False" << endl;
	//string f = "(1>2)+(2+(3<5))*4-5%2";
	//cout << "中缀表达式为:" << f << endl;
	//cout << "对应前缀表达式为:";
	//stack<string> s6 = M.MiddleexToPrevex(f);
	//C.PutStack(s6);
	//P.Cal_Preex(s6);
	//cout << "\n-------------------------\n";

	////增加了多位符号的逻辑计算，逻辑大于等于，小于等于，不等于，等于等于
	//cout << "扩展了多位符号的逻辑计算，逻辑大于等于，小于等于，不等于，等于等于，扩展了符号类支持的类型" << endl;
	//string g = "(1>2)+(2+(3<=5))*4-5%2+(1!=2)+2==14";
	//cout << "中缀表达式为:" << g << endl;
	//cout << "对应前缀表达式为:";
	//stack<string> s7 = M.MiddleexToPrevex(g);
	//C.PutStack(s7);
	//P.Cal_Preex(s7);
	//cout << "\n-------------------------\n";


	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧:
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件



