#include "CallFunction.h"
#include "PreTreatAndStandard.h"
#include<windows.h>
#include<cstdio> 
#include<string>
#include<algorithm>
//void ShowTitle() {
//	cout << "-------------------------------------------------------------------" << endl;
//	cout << "C++表达式解析器，支持整数，小数四则运算，逻辑运算，函数调用顺序解析" << endl;
//	cout << "-------------------------------------------------------------------" << endl;
//}


double CallFunction::callFunction(string expressionStrng)
{
	MidexToPreex M;
	PreexParAndEva P;
	//FunctionExpression F;
	CommonStackMethod<string> C;
	SymbolSetAndPriority OPS;
	//SuffixFunctionEva SFE;
	string a;
	PreTreatAndStandard PTAS;
	//MessageBox(NULL, "对话框测试", "测试标题", MB_OK);
	a = expressionStrng;
	if (a == "\n" || a == " " || a == "\t" || a == "")
	{
		return 0;
	}

	
	bool valid = true;
	for (int i = 0; i < a.length(); i++)
	{
		//如果不是全角字符
		if (!(a[i] >= 0 && a[i] <= 127)) {
			valid = false;
			break;
		}
	}
	if (!valid)//如果字符不合法，提示错误并重新输入
	{
		//cout << "语法错误，请检查是否输入了中文字符，例如中文括号" << endl;
		string ErrorInfo = "语法错误，请检查是否输入了中文字符，例如中文括号!\n出现错误的表达式为:";
		ErrorInfo.append(a);
		MessageBox(NULL, ErrorInfo.c_str(), "Error", MB_OK);
		return 0;
	}

	//开始预处理 判断是否要进行语法转换 例如将SUM PARAM 4 IPARAM 1   ->   SUM(PARAM[4],IPARAM[1])
	for (int i = 0; i < a.length(); i++)
	{
		ostringstream changestr;
		if (isalpha(a[i]))
		{
			for (int j = i; j < a.length() && isalnum(a[j]); j++, i++)
			{
				changestr << a[j];
			}
			string AttrName = changestr.str();
			transform(AttrName.begin(),AttrName.end(),AttrName.begin(),::toupper);
			string AttrType = FunctionParaSettings::FindType[AttrName];

			if (AttrType == "Array" && a[i] != '[' || AttrType == "Function" && a[i] != '(')
			{
				//cout << "需进行语法转换预处理" << endl;
				string WariningInfo = "出现了语法转换预处理情况，请检查函数调用后是否多加了空格！\n出现错误的表达式为:";
				WariningInfo.append(a);
				MessageBox(NULL, WariningInfo.c_str(), "Warning", MB_OK);
				a = PTAS.InputNormalizationg(a);
				break;
			}
		}
	}
	//开始判断输入的括号是否匹配

	int leftpare = 0;
	int rightpare = 0;
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == '(')
		{
			leftpare++;
		}
		else if (a[i] == ')')
		{
			rightpare++;
		}
	}
	if (leftpare != rightpare)
	{
		//cout << "括号不匹配，请检查你的输入" << endl;
		string ErrorInfo = "括号不匹配，请检查你的输入!\n出现错误的表达式为:";
		ErrorInfo.append(a);
		MessageBox(NULL, ErrorInfo.c_str(), "Error", MB_OK);
		return 0;
	}




	//cout << "中缀表达式为:" << a << endl;
	stack<string> s = M.MiddleexToPrevex(a);
	//cout << "对应前缀表达式为:";
	C.PutStack(s);
	double value=P.Cal_Preex(s);
	//cout << "\n-------------------------\n";
	return value;


	//ShowTitle();
	////实现 异常字符识别 四则运算和函数解析自动判断并调用对应接口
	//while (true) {
	//		cout << ">>> ";
	//		getline(cin, a);
	/*
			if (a=="\n"||a==" "||a=="\t"||a=="")
			{
				continue;
			}

			if (a=="exit()")
			{
				break;
			}
			if (a == "cls()") {
				system("cls");
				ShowTitle();
				continue;
			}
			bool valid = true;
			for (int i = 0; i < a.length(); i++)
			{
				//如果不是全角字符
				if (!(a[i] >= 0 && a[i] <= 127)) {
					valid = false;
					break;
				}
			}
			if (!valid)//如果字符不合法，提示错误并重新输入
			{
				cout << "语法错误，请检查是否输入了中文字符，例如中文括号" << endl;
				continue;
			}

			//开始预处理 判断是否要进行语法转换 例如将SUM PARAM 4 IPARAM 1   ->   SUM(PARAM[4],IPARAM[1])
			for (int i = 0; i < a.length(); i++)
			{
				ostringstream changestr;
				if (isalpha(a[i]))
				{
					for (int j = i; j < a.length() && isalnum(a[j]); j++, i++)
					{
						changestr << a[j];
					}
					string AttrName = changestr.str();

					string AttrType = FunctionParaSettings::FindType[AttrName];

					if (AttrType == "Array"&&a[i]!='['||AttrType=="Function"&&a[i]!='(')
					{
						cout << "需进行语法转换预处理"<<endl;
						a = PTAS.InputNormalizationg(a);
						break;
					}
				}
			}
			//开始判断输入的括号是否匹配

			int leftpare = 0;
			int rightpare = 0;
			for (int i = 0; i < a.length(); i++)
			{
				if (a[i]=='(')
				{
					leftpare++;
				}
				else if (a[i]==')')
				{
					rightpare++;
				}
			}
			if (leftpare!=rightpare)
			{
				cout << "括号不匹配，请检查你的输入" << endl;
				continue;
			}




			cout << "中缀表达式为:" << a << endl;
			stack<string> s = M.MiddleexToPrevex(a);
			cout << "对应前缀表达式为:";
			C.PutStack(s);
			P.Cal_Preex(s);
			cout << "\n-------------------------\n";
			*/

	//		//(PARA[1]/2-PARA[4]-(PARA[2]/2-PARA[3]/2)/2*TAN(8))
	//		//if (flag2)
	//		////if(flag1)
	//		//{
	//		//	cout << "中缀表达式为:" << a << endl;
	//		//	cout << "表达式为函数调用解析" << endl;
	//		//	cout << "对应后缀表达式为:";
	//		//	stack<string> s = F.FuncExpression(a);
	//		//	C.PutStack(s);
	//		//	//cout << "计算过程如下:" << endl;
	//		//	cout <<"最终计算结果为:"<< SFE.SuffixFuncEva(s) << endl;
	//		//	cout << "-------------------------\n";
	//		//}
	//		//else
	//		//{
	//		//	cout << "中缀表达式为:" << a << endl;
	//		//	cout << "表达式为四则运算或者逻辑运算" << endl;
	//		//	cout << "对应前缀表达式为:";
	//		//	stack<string> s = M.MiddleexToPrevex(a);
	//		//	C.PutStack(s);
	//		//	P.Cal_Preex(s);
	//		//	cout << "\n-------------------------\n";
	//		//}


	//}
}
