#include "SuffixFunctionEva.h"
#include "FunctionParaSettings.h"
#include "FunCaculate.h"
#include "CallFunction.h"
#include<sstream>
//建立2个栈，分别为参数栈，方法栈，后缀表达式从左往右扫描，遇到参数入栈s1,
//遇到方法，从settings里查询方法需要一个参数，然后从s1中取出对应个数的参数并进行运算，将运算结果作为新的参数存回s1
double SuffixFunctionEva::SuffixFuncEva(stack<string> s)
{
	stack<double> s1;
	stack<string> s2;	
	//FunctionParaSettings FPS;
	FunCaculate FC;

	/*while (!s.empty())
	{
		bool containsOp = false;
		for (int i = 0; i < s.top().length(); i++)
		{
			if (s.top()[i] == '+' || s.top()[i] == '-' || s.top()[i] == '*' || s.top()[i] == '/'||s.top()[i]=='>'||s.top()[i]=='<' || s.top()[i] == '=' || s.top()[i] == '&' || s.top()[i] == '|')
			{
				containsOp = true;
				break;
			}
		}
		double top;
		if (containsOp)
		{
			CallFunction CF;
			top = CF.callFunction(s.top());
			s.pop();
			s.push(to_string(top));
			break;
		}
		else
		{
			break;
		}
		
	}*/

	while (!s.empty())
	{
		//先判断栈顶是否为表达式，若是 则递归计算
		bool containsOp = false;
		for (int i = 0; i < s.top().length(); i++)
		{
			if (s.top()[i] == '+' || s.top()[i] == '-' || s.top()[i] == '*' || s.top()[i] == '/' || s.top()[i] == '>' || s.top()[i] == '<' || s.top()[i] == '=' || s.top()[i] == '&' || s.top()[i] == '|')
			{
				containsOp = true;
				break;
			}
		}
		double top;
		if (containsOp)
		{
			CallFunction CF;
			top = CF.callFunction(s.top());
			s.pop();
			s.push(to_string(top));
			//break;
		}
		//准备开始出栈传入栈，判断栈顶元素是否含有一对括号，如果有，说明是方法，如果没有，说明是参数
		bool isMethod = false;
		for (int i = 0; i < s.top().length(); i++)
		{	
			if (s.top()[i]=='(' && s.top()[i+1]==')')
			{
				isMethod = true;
				break;
			}
		}
		if (isMethod)  //如果是方法
		{
			//cout << s.top() << endl;
			//int paraCount=FPS.FuncitonPara[s.top()];  //查询当前方法所需参数个数
			int paraCount=FunctionParaSettings::FuncitonPara[s.top()];  //查询当前方法所需参数个数
			double* s3 = new double[paraCount];
			for (int i = 0; i < paraCount; i++)  //从s1中取出指定个数的参数，存入s3
			{
				s3[i] = s1.top();
				s1.pop();
			}
			//for (int i = paraCount-1; i >= 0; i--)
			//{
			//	cout << s3[i]<<" ";
			//}
			//cout << s.top() << endl;
			//实现方法进行计算，传参方法名，参数数组s3，例如FunCalcute(s.top,s3) 返回计算结果
			double result=FC.FuncCaculte(s.top(), s3);
			s1.push(result);  //将方法，参数一起的计算结果push到s1
			//cout <<"本次方法运算结果为:"<< result << endl;
			s.pop();
		}
		else //不是方法，那就是参数，判断是参数是直接给的数字，还是属性名，如果是属性名，再判断是不是数组调用
		{
			bool isAttr = false;
			for (int i = 0; i < s.top().length(); i++)
			{
				if ((s.top()[i] >= 'a' && s.top()[i] <= 'z') || (s.top()[i] >= 'A' && s.top()[i] <= 'Z')) {
					isAttr = true;
					break;
				}
			}
			if (isAttr)
			{
				//判断是属性值还是数组访问
				bool isArray = false;
				for (int i = 0; i < s.top().length(); i++)
				{
					if (s.top()[i] == '[')
					{
						isArray = true;
						break;
					}
				}
				if (isArray)
				{
					
					stringstream num;
					for (int i = 1; i <= s.top().length(); i++)
					{
						if (s.top()[i-1]=='[')
						{
							for (int j = i; j < s.top().length()-1; j++)
							{
								num << s.top()[j];
							}
						}
					}

					//开始提取数组名
					ostringstream nameStr;
					//for (int l = 0; l < s.top().size() && isalpha(s.top()[l]); l++)
					bool Ops=false;
					for (int l = 0; l < s.top().size(); l++)
					{
						if (isalpha(s.top()[l]))
						{
							nameStr << s.top()[l];
						}
						if (s.top()[l]=='-')
						{
							Ops = true;
						}
					}


					int index=0;
					num >> index;
					//double funValue = FPS.StringNameToArray[nameStr.str()][index];
					double ArraySize = FunctionParaSettings::StringNameToArray[nameStr.str()].size();
					double funValue;
					if (index > ArraySize)
					{
						funValue = 0;
					}
					else
					{
						funValue = FunctionParaSettings::StringNameToArray[nameStr.str()][index - 1];
					}
					//cout << s.top() << "参数的值为" << funValue << endl;
					double doubleStr = funValue;
					if (Ops)
					{
						doubleStr = -doubleStr;
					}
					s1.push(doubleStr);
					s.pop();
				}
				else
				{
					//查询属性对应值并转为double
					//double funValue = FPS.funcValue[s.top()];
					double funValue = FunctionParaSettings::funcValue[s.top()];
					//cout << s.top() << "参数的值为" << funValue << endl;
					double doubleStr = funValue;
					s1.push(doubleStr);
					s.pop();
				}	
			}
			else
			{
				//CallFunction CF;
				//double doubleStr = CF.callFunction(s.top());
				double doubleStr = atof(s.top().c_str());
				//cout << doubleStr << endl;
				s1.push(doubleStr);
				s.pop();
			}
			
		}	
		
	}
	return double(s1.top());

}
