#include "SuffixFunctionEva.h"
#include "FunctionParaSettings.h"
#include "FunCaculate.h"
#include "CallFunction.h"
#include<sstream>
//����2��ջ���ֱ�Ϊ����ջ������ջ����׺���ʽ��������ɨ�裬����������ջs1,
//������������settings���ѯ������Ҫһ��������Ȼ���s1��ȡ����Ӧ�����Ĳ������������㣬����������Ϊ�µĲ������s1
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
		//���ж�ջ���Ƿ�Ϊ���ʽ������ ��ݹ����
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
		//׼����ʼ��ջ����ջ���ж�ջ��Ԫ���Ƿ���һ�����ţ�����У�˵���Ƿ��������û�У�˵���ǲ���
		bool isMethod = false;
		for (int i = 0; i < s.top().length(); i++)
		{	
			if (s.top()[i]=='(' && s.top()[i+1]==')')
			{
				isMethod = true;
				break;
			}
		}
		if (isMethod)  //����Ƿ���
		{
			//cout << s.top() << endl;
			//int paraCount=FPS.FuncitonPara[s.top()];  //��ѯ��ǰ���������������
			int paraCount=FunctionParaSettings::FuncitonPara[s.top()];  //��ѯ��ǰ���������������
			double* s3 = new double[paraCount];
			for (int i = 0; i < paraCount; i++)  //��s1��ȡ��ָ�������Ĳ���������s3
			{
				s3[i] = s1.top();
				s1.pop();
			}
			//for (int i = paraCount-1; i >= 0; i--)
			//{
			//	cout << s3[i]<<" ";
			//}
			//cout << s.top() << endl;
			//ʵ�ַ������м��㣬���η���������������s3������FunCalcute(s.top,s3) ���ؼ�����
			double result=FC.FuncCaculte(s.top(), s3);
			s1.push(result);  //������������һ��ļ�����push��s1
			//cout <<"���η���������Ϊ:"<< result << endl;
			s.pop();
		}
		else //���Ƿ������Ǿ��ǲ������ж��ǲ�����ֱ�Ӹ������֣�����������������������������ж��ǲ����������
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
				//�ж�������ֵ�����������
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

					//��ʼ��ȡ������
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
					//cout << s.top() << "������ֵΪ" << funValue << endl;
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
					//��ѯ���Զ�Ӧֵ��תΪdouble
					//double funValue = FPS.funcValue[s.top()];
					double funValue = FunctionParaSettings::funcValue[s.top()];
					//cout << s.top() << "������ֵΪ" << funValue << endl;
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
