#include "FunctionExpression.h"
#include<iostream>
#include<stack>
#include<sstream>
#include<string>
#include "SymbolSetAndPriority.h"
#include "CommonStackMethod.h"
using namespace std;
/*ʵ�ֽ����������õ���׺���ʽת��׺���ʽ
ʵ���߼�Ϊ������3��ջ���ֱ�洢�����������ţ����
������ɨ�躯�����ã�����������������s1�����������ţ�����s2���������֣�����s3
����������ѹ��s2��Ȼ����������s1ջ����һ������������s3��Ȼ����������s2�е�һ�����ŷ���s3
��������ɨ�裬ֱ������
������s3����Ϊ������Ҫ�Ľ��
example:����max(abs(random(-9,-1)),random(1,9)),���-9, -1, random, (), abs, (), 1, 9, random, (), max, ()

int((OutBore+200)/2)
int((200+OutBore)/2)
*/

stack<string> FunctionExpression::FuncExpression(string& midex) 
{
	CommonStackMethod<string> C;
	stack<string>s1, s3;//��������ջ���ֱ�Ϊ������ջ������ջ�����ջ
	stack<char>s2;

	int midex_len = midex.size();

	for (int i = 0; i < midex_len; i++)
	{
		//max(abs(random(-9, -1)), random(1, 9))
		//max(abs(random(func1, -10)), random(1, func2))
		if ((midex[i] >= 'a' && midex[i] <= 'z') || (midex[i] >= 'A' && midex[i] <= 'Z'))
		{
			ostringstream strtmp;  //������������string
			if (s2.size() > s1.size())
			{
				for (int k = 0; k < s2.size() - s1.size(); k++)
				{
					strtmp << '(';
				}
			}
			//���Ǻ����� ͨ�����������ķ����ж����Ǻ������� �������Է��� ����Ǻ���ѹ��s1 ��������ѹ��s3
			for (int j = i; midex[j] != '(' &&midex[j]!=','&& j < midex_len; j++, i++)
			{
				if (midex[j]==')'&&s1.size()==s2.size())
				{
					break;
				}
				else if(midex[j] == ')' && s1.size() != s2.size())
				{
					strtmp << midex[j];
					s2.pop();
				}
				else
				{
					strtmp << midex[j];
				}
				
			}
			if (midex[i]=='(')
			{
				string a = strtmp.str();
				s1.push(a);  //����������ѹ��s1
			}
			else if (midex[i]==','||(midex[i]==')'))
			{
				string a = strtmp.str();
				s3.push(a); //ѹ��s3
			}
			else
			{
				cout << "(warning�������﷨���ܲ��Ϸ�����������)";
				string a = strtmp.str();
				s3.push(a);
			}
			i--;//�����һ�� ��Ҫ������
			
		}

		//������else if �����Ż���һ��elseif����֧������λ�� 
		//max(abs(random(-9, -1)), random(1, 9))
		
		else if ((midex[i] >= '0' && midex[i] <= '9') || midex[i] == '-') //��Ϊ�������߸��� ����ɨ�赽��һ�����Ż���������Ϊֹ תΪstringѹ��s3
		{
			ostringstream numtmp;
			if (s2.size() > s1.size())
			{
				for (int k = 0; k < s2.size() - s1.size(); k++)
				{
					numtmp << '(';
				}
			}
			for (int j = i; midex[j] != ','; j++, i++)
			{
				if (midex[j] == ')' && s1.size() == s2.size())
				{
					break;
				}
				else if (midex[j] == ')' && s1.size() != s2.size())
				{
					numtmp << midex[j];
					s2.pop();
				}
				else
				{
					numtmp << midex[j];
				}


			}
			i--;//�����һ�� ��Ҫ������
			string b = numtmp.str();
			s3.push(b);//����������ѹ��s3
		}

		else if (midex[i] == '(') //��Ϊ������ ֱ��ѹ��s2
		{
			s2.push(midex[i]);
		}

		else if (midex[i] == ')')//��Ϊ�����ţ�ѹ��s2��Ȼ����������s1ջ����һ��������������һ�����ŷ���s3��Ȼ����������s2�е�һ������
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