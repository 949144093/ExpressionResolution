#include "FunctionExpression.h"
#include<iostream>
#include<stack>
#include<sstream>
#include<string>
#include "SymbolSetAndPriority.h"
#include "CommonStackMethod.h"
using namespace std;
/*实现解析函数调用的中缀表达式转后缀表达式
实现逻辑为，建立3个栈，分别存储函数名，括号，结果
从左到右扫描函数调用，遇到函数名，存入s1，遇到左括号，存入s2，遇到数字，存入s3
遇到右括号压入s2，然后立即弹出s1栈顶的一个函数名放入s3，然后立即弹出s2中的一对括号放入s3
继续往后扫描，直到结束
最后输出s3，即为我们需要的结果
example:输入max(abs(random(-9,-1)),random(1,9)),输出-9, -1, random, (), abs, (), 1, 9, random, (), max, ()
*/

stack<string> FunctionExpression::FuncExpression(string& midex) 
{
	CommonStackMethod<string> C;
	stack<string>s1, s3;//建立三个栈，分别为函数名栈，括号栈，结果栈
	stack<char>s2;

	int midex_len = midex.size();

	for (int i = 0; i < midex_len; i++)
	{
		//max(abs(random(-9, -1)), random(1, 9))
		//max(abs(random(func1, -10)), random(1, func2))
		if ((midex[i] >= 'a' && midex[i] <= 'z') || (midex[i] >= 'A' && midex[i] <= 'Z'))
		{

			ostringstream strtmp;  //建立流来保存string
			//若是函数名 通过结束遇到的符号判断他是函数调用 还是属性方法 如果是函数压入s1 若是属性压入s3
			for (int j = i; midex[j] != '(' &&midex[j]!=','&&midex[j]!=')'&& j < midex_len; j++, i++)
			{
				strtmp << midex[j];
			}
			if (midex[i]=='(')
			{
				string a = strtmp.str();
				s1.push(a);  //将完整数据压入s1
			}
			else if (midex[i]==','||midex[i]==')')
			{
				string a = strtmp.str();
				s3.push(a); //压入s3
			}
			else
			{
				cout << "(warning：输入语法可能不合法，请检查输入)";
				string a = strtmp.str();
				s3.push(a);
			}
			i--;//多加了一次 需要减回来
			
		}

		//下面俩else if 可以优化成一个elseif并且支持任意位数 
		//max(abs(random(-9, -1)), random(1, 9))
		
		else if ((midex[i] >= '0' && midex[i] <= '9') || midex[i] == '-') //若为正数或者负号 往后扫描到下一个逗号或者右括号为止 转为string压入s3
		{
			ostringstream numtmp;
			for (int j = i; midex[j] != ',' && midex[j] != ')'; j++, i++)
			{
				numtmp << midex[j];
			}
			i--;//多加了一次 需要减回来
			string b = numtmp.str();
			s3.push(b);//将完整数字压入s3
		}

		else if (midex[i] == '(') //若为左括号 直接压入s2
		{
			s2.push(midex[i]);
		}

		else if (midex[i] == ')')//若为右括号，压入s2，然后立即弹出s1栈顶的一个函数名并连接一对括号放入s3，然后立即弹出s2中的一对括号
		{
			s2.push(midex[i]);
			ostringstream funtmp;
			funtmp << s1.top();
			funtmp << "()";
			s3.push(funtmp.str());
			s1.pop();

			s2.pop();
			s2.pop();
		}
	}
	s3 = C.ReversalStack(s3);
	return s3;
}