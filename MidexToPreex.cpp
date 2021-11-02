#include "MidexToPreex.h"
#include <iostream>
#include <stack>
#include <sstream>
#include "SymbolSetAndPriority.h"
#include "CharToString.h"
#include "FunctionParaSettings.h"
#include "FunctionExpression.h"
#include "CommonStackMethod.h"
#include "SuffixFunctionEva.h"
using namespace std;


stack<string> MidexToPreex::MiddleexToPrevex(string& midex) {
	stack<string> s1;
	stack<string> s2; //初始化运算符栈s1和中间结果栈s2
	SymbolSetAndPriority OPS;//实例化符号参数方法
	CharToString CTS;//实例化字符转string方法
	//FunctionParaSettings FPS;
	FunctionExpression F;
	CommonStackMethod<string> C;
	SuffixFunctionEva SFE;
	int midex_len = midex.size();  //定义string长度

	//先扫描内部是否含有单引号，有单引号的话，将单引号内对应的字符串替换为对应的double类型
	//AB->65+POW(128,0)+66*pow(128,1)
	ostringstream changString;
	int start_pos;
	int end_pos;
	for (int i = 0; i < midex_len; i++)
	{
		
		if (midex[i]=='\'')
		{
			start_pos = i;
			for (int j = i+1; midex[j]!='\''; j++)
			{
				changString << midex[j];
				end_pos = j;
			}
			//将提取出来的DoubleString转换为数字并替换
			//计算数字
			string DoubleString = changString.str();
			//cout << DoubleString;
			double DoubleStringValue = 0.0;
			for (int i = 0; i < DoubleString.size(); i++)
			{
				DoubleStringValue += int(DoubleString[i]) * pow(128, i);
			}
			//cout << DoubleStringValue;
			//替换单引号以及相应内容为对应数字
			midex.replace(start_pos, end_pos - start_pos + 2, to_string(DoubleStringValue));
			midex_len = midex.size();
			break;
		}
	}

	bool warning = false;
	//先扫描四则运算内部是否含有英文字符，若有，查询属性或者数组的值，并将string内容替换为对应的值，若为函数调用，计算函数调用返回值并替换
	for (int i = 0; i < midex_len; i++)
	{
		if (isalpha(midex[i])|| (midex[i]=='_')||(midex[i]=='\''))
		{
			warning = true;
			int pos = i;//记录字符串替换的起始位置
			ostringstream changeStr;
			bool isArray = false;
			bool isFunc = false;
			int LeftBracket = 0;
			int RightBracket = 0;
			//从左往右扫描 遇到字母或者数字或者下划线就写入changeStr字符串，遇到不是字母或者不是括号就停止
			for (int j = i; (isalnum(midex[j])||(midex[j]=='_')||midex[j]=='['||midex[j]=='(')&&j < midex_len; j++,i++)
			{
				if (isalnum(midex[j]) || (midex[j] == '_'))
				{
					changeStr << midex[j];
				}
				else if (midex[j] == '[')
				{
					isArray = true;
					for (int k = j; midex[k]!=']';k++,i++)
					{
						changeStr << midex[k];
					}
					changeStr << ']';
					break;
				}
				else if (midex[j]=='(')
				{
					isFunc = true;
					for (int k = j;k<midex_len; k++,i++)
					{
						changeStr << midex[k];
						if (midex[k]=='(')
						{
							LeftBracket++;
						}
						else if (midex[k]==')')
						{
							RightBracket++;
						}
						if (LeftBracket==RightBracket)
						{
							break;
						}
					}
					break;
				}
			}
			//cout << midex[i];
			//i--;
			int n = i;//记录字符串替换的结束位置
			string changeS = changeStr.str();
			if (isArray)
			{	//如果是数组，提取数组中间的数字，然后去查询对应的值，存到NewchangeS里
				stringstream numStr;
				for (int m = 0; m < changeS.size(); m++)
				{
					if (changeS[m] == '[')
					{
						for (int n = m + 1; n < changeS.size() - 1; n++)
						{
							//cout << changeS[n];
							numStr << changeS[n];
						}

					}
				}
				int index = 0;
				numStr >> index;  //提取的数字存到index内

				//开始提取数组名
				ostringstream nameStr;
				for (int l = 0; l < changeS.size()&&(isalnum(changeS[l])||(changeS[l]=='_')); l++)
				{
					if (isalnum(changeS[l]) || (changeS[l] == '_'))
					{
						nameStr << changeS[l];
					}
				}

				//修改此处
				//double NewchangeS = FPS.StringNameToArray[nameStr.str()][index];
				//判断数组访问是否越界
				double ArraySize = FunctionParaSettings::StringNameToArray[nameStr.str()].size();
				double NewchangeS;
				if (index> ArraySize)
				{
					NewchangeS = 0;
				}
				else
				{
					NewchangeS = FunctionParaSettings::StringNameToArray[nameStr.str()][index - 1];
				}
				
				//cout << "参数的值为" << NewchangeS << endl;
				
				//用NewchangeS的值替换数组或者属性
				midex.replace(pos,n-pos+1,to_string(NewchangeS));


				//cout << "\n数组新字符串为" << midex << endl;
				midex_len = midex.size();
				i = 0;
			}
			else if (isFunc)
			{

				//cout <<"提取出来的函数部分为："<<changeS<<endl;
				stack<string> s = F.FuncExpression(changeS);
				//C.PutStack(s);
				//cout <<"最终计算结果为:"<< SFE.SuffixFuncEva(s) << endl;
				midex.replace(pos, n - pos+1, to_string(SFE.SuffixFuncEva(s)));
				midex_len = midex.size();
				i = 0;
			}
			else if (changeS=="TIMES"||changeS=="DIV"||changeS=="ADD"||changeS=="SUB")
			{
				//如果发现属性是关键字 去查询关键字替换
				//string symbol = FPS.SymbolReplace[changeS];
				string symbol = FunctionParaSettings::SymbolReplace[changeS];
				midex.replace(pos, n-pos, symbol);
				midex_len = midex.size();
				i = 0;
			}
			else if (changeS=="RPRO")
			{
				midex.replace(pos-1, n - pos+2, "");
				midex_len = midex.size();
				i = 0;
			}
			else 
			{
				//查询属性对应值并转为double
				//double funValue = FPS.funcValue[changeS];
				double funValue = FunctionParaSettings::funcValue[changeS];
				//cout << "参数的值为" << funValue << endl;
				//用NewchangeS替换里面的字符
				midex.replace(pos, n-pos, to_string(funValue));
				//cout << "\n属性新字符串为" << midex << endl;
				midex_len = midex.size();
				i = 0;
			}
			
		}
	}
	//1 + MAX(ABS(RANDOM(-10, a[3])), RANDOM(1, func2)) + a[3]
	/*if (warning)
	{
		cout << "(Warning：输入语法可能不合法，输出结果可能不一定符合预期！)";
	}*/
	//进行负数处理，情况大致有如下两种 -替换为(0-1)*
	//-5+2+3*4，第一位为负号，从左往右扫描，如果第一个是负号，替换为(0-1)*5+2+3*4
	//1+2+3+(-2+4)   括号内第一位为负号，替换为1+2+3+((0-1)*2+4)
	//5 * -2 * 5  替换为5 * (0-1)*2 * 5
	for (int i = 0; i < midex.length(); i++)
	{
		if (midex[i]=='-')
		{
			if (i==0)
			{
				midex.replace(0, 1, "(0-1)*");
			}
			else if (midex[i-1]=='('|| OPS.ops.find(CTS.CharToStr(midex[i - 1])) != OPS.ops.end()|| (midex[i - 1] == ' ' && OPS.ops.find(CTS.CharToStr(midex[i - 2])) != OPS.ops.end()))
			{
				midex.replace(i, 1, "(0-1)*");
			}
		/*	else if (OPS.ops.find(CTS.CharToStr(midex[i-1])) != OPS.ops.end())
			{
				midex.replace(i, 1, "(0-1)*");
			}
			else if (midex[i - 1]==' '&&OPS.ops.find(CTS.CharToStr(midex[i - 2])) != OPS.ops.end())
			{
				midex.replace(i, 1, "(0-1)*");
			}*/
		}
	}
	midex_len = midex.size();

	//cout <<"表达式预解析过后变为："<<midex<<endl;

	for (int i = midex_len - 1; i >= 0; i--) { //从右往左扫描
		//string midexi(1, midex[i]);  //将当前字符转为string
		if (midex[i] >= '0' && midex[i] <= '9' || midex[i] == '.') {

			//若为操作数，设置新循环往前读取压到临时栈直到下一个操作符为止，将所有的操作数通过流合成一个完整的多位数或者小数后压入s2，例如507,3.62这种
			//stack<char> num_tmp;
			ostringstream strtmp;  //建立流来保存string
			for (int j = i; j >= 0 && (midex[j] >= '0' && midex[j] <= '9' || midex[j] == '.' || midex[j] == ' ' || midex[j] == '\t'); j--, i--) //从后往前读取，直到下一个操作符为止
			{
				if (midex[j] == ' ' || midex[j] == '\t') //处理多余的无用空格
				{
					continue;
				}
				else
					strtmp<<midex[j];
			}
			i++;  //因为for里面多减了一次索引，需要加一次
			
			string a = strtmp.str();
			string s(a.rbegin(), a.rend()); //字符串逆序
			s2.push(s);  //将完整数据压入s2

		}
		//(1>2)+(2+(3<=5))*4-5%2
		else if (OPS.ops.find(CTS.CharToStr(midex[i])) != OPS.ops.end()) { //若为运算符，先判断运算符是单位还是多位的，然后与s1栈顶进行优先级比较（标记操作1）
			ostringstream opstmp;
			for (int j = i; j >= 0 && OPS.ops.find(CTS.CharToStr(midex[j])) != OPS.ops.end(); j--,i--)
			{
				opstmp << midex[j];
			}
			string tem = opstmp.str();
			string b(tem.rbegin(),tem.rend());

			i++;

			if (b.size() == 1) {
				while (true) {
					string midexi(1, midex[i]);
					if (s1.empty() || s1.top()[0] == ')') { //若s1为空或者栈顶为右括号，运算符入栈s1
						string str(1, midex[i]);
						s1.push(str);
						break;
					}
					else if (OPS.priority[midexi] >= OPS.priority[s1.top()]) { //若当前元素优先级比栈顶元素高或相等，入栈s1
						string str(1, midex[i]);
						s1.push(str);
						break;
					}
					else if (OPS.priority[midexi] < OPS.priority[s1.top()]) { //若优先级低，s1栈顶运算符压入s2并出栈,然后继续与s1栈顶运算符比较，重复标记操作1
						s2.push(s1.top());
						s1.pop();
						continue;
					}
				}
			}
			else
			{
				while (true) {
					if (s1.empty() || s1.top()[0] == ')') { //若s1为空或者栈顶为右括号，运算符入栈s1
						s1.push(b);
						break;
					}
					else if (OPS.priority[b] >= OPS.priority[s1.top()]) { //若当前元素优先级比栈顶元素高或相等，入栈s1
						s1.push(b);
						break;
					}
					else if (OPS.priority[b] < OPS.priority[s1.top()]) { //若优先级低，s 1栈顶运算符压入s2并出栈,然后继续与s1栈顶运算符比较，重复标记操作1
						s2.push(s1.top());
						s1.pop();
						continue;
					}
				}
			}
		
		}

		else if (midex[i] == ')') { //遇到右括号直接压入s1
			string str(1, midex[i]);
			s1.push(str);
		}

		else if (midex[i] == '(') { //遇到左括号，依次弹出s1栈顶到s2，遇到右括号停止，并将一对括号丢弃
			while (s1.top()[0] != ')') {
				s2.push(s1.top());
				s1.pop();
			}
			s1.pop();//丢弃右括号
		}
	}
	//扫描完毕，将S1剩余运算符依次弹出压到S2
	while (!s1.empty()) {
		s2.push(s1.top());
		s1.pop();
	}
	return s2;
}

