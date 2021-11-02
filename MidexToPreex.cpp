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
	stack<string> s2; //��ʼ�������ջs1���м���ջs2
	SymbolSetAndPriority OPS;//ʵ�������Ų�������
	CharToString CTS;//ʵ�����ַ�תstring����
	//FunctionParaSettings FPS;
	FunctionExpression F;
	CommonStackMethod<string> C;
	SuffixFunctionEva SFE;
	int midex_len = midex.size();  //����string����

	//��ɨ���ڲ��Ƿ��е����ţ��е����ŵĻ������������ڶ�Ӧ���ַ����滻Ϊ��Ӧ��double����
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
			//����ȡ������DoubleStringת��Ϊ���ֲ��滻
			//��������
			string DoubleString = changString.str();
			//cout << DoubleString;
			double DoubleStringValue = 0.0;
			for (int i = 0; i < DoubleString.size(); i++)
			{
				DoubleStringValue += int(DoubleString[i]) * pow(128, i);
			}
			//cout << DoubleStringValue;
			//�滻�������Լ���Ӧ����Ϊ��Ӧ����
			midex.replace(start_pos, end_pos - start_pos + 2, to_string(DoubleStringValue));
			midex_len = midex.size();
			break;
		}
	}

	bool warning = false;
	//��ɨ�����������ڲ��Ƿ���Ӣ���ַ������У���ѯ���Ի��������ֵ������string�����滻Ϊ��Ӧ��ֵ����Ϊ�������ã����㺯�����÷���ֵ���滻
	for (int i = 0; i < midex_len; i++)
	{
		if (isalpha(midex[i])|| (midex[i]=='_')||(midex[i]=='\''))
		{
			warning = true;
			int pos = i;//��¼�ַ����滻����ʼλ��
			ostringstream changeStr;
			bool isArray = false;
			bool isFunc = false;
			int LeftBracket = 0;
			int RightBracket = 0;
			//��������ɨ�� ������ĸ�������ֻ����»��߾�д��changeStr�ַ���������������ĸ���߲������ž�ֹͣ
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
			int n = i;//��¼�ַ����滻�Ľ���λ��
			string changeS = changeStr.str();
			if (isArray)
			{	//��������飬��ȡ�����м�����֣�Ȼ��ȥ��ѯ��Ӧ��ֵ���浽NewchangeS��
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
				numStr >> index;  //��ȡ�����ִ浽index��

				//��ʼ��ȡ������
				ostringstream nameStr;
				for (int l = 0; l < changeS.size()&&(isalnum(changeS[l])||(changeS[l]=='_')); l++)
				{
					if (isalnum(changeS[l]) || (changeS[l] == '_'))
					{
						nameStr << changeS[l];
					}
				}

				//�޸Ĵ˴�
				//double NewchangeS = FPS.StringNameToArray[nameStr.str()][index];
				//�ж���������Ƿ�Խ��
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
				
				//cout << "������ֵΪ" << NewchangeS << endl;
				
				//��NewchangeS��ֵ�滻�����������
				midex.replace(pos,n-pos+1,to_string(NewchangeS));


				//cout << "\n�������ַ���Ϊ" << midex << endl;
				midex_len = midex.size();
				i = 0;
			}
			else if (isFunc)
			{

				//cout <<"��ȡ�����ĺ�������Ϊ��"<<changeS<<endl;
				stack<string> s = F.FuncExpression(changeS);
				//C.PutStack(s);
				//cout <<"���ռ�����Ϊ:"<< SFE.SuffixFuncEva(s) << endl;
				midex.replace(pos, n - pos+1, to_string(SFE.SuffixFuncEva(s)));
				midex_len = midex.size();
				i = 0;
			}
			else if (changeS=="TIMES"||changeS=="DIV"||changeS=="ADD"||changeS=="SUB")
			{
				//������������ǹؼ��� ȥ��ѯ�ؼ����滻
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
				//��ѯ���Զ�Ӧֵ��תΪdouble
				//double funValue = FPS.funcValue[changeS];
				double funValue = FunctionParaSettings::funcValue[changeS];
				//cout << "������ֵΪ" << funValue << endl;
				//��NewchangeS�滻������ַ�
				midex.replace(pos, n-pos, to_string(funValue));
				//cout << "\n�������ַ���Ϊ" << midex << endl;
				midex_len = midex.size();
				i = 0;
			}
			
		}
	}
	//1 + MAX(ABS(RANDOM(-10, a[3])), RANDOM(1, func2)) + a[3]
	/*if (warning)
	{
		cout << "(Warning�������﷨���ܲ��Ϸ������������ܲ�һ������Ԥ�ڣ�)";
	}*/
	//���и������������������������ -�滻Ϊ(0-1)*
	//-5+2+3*4����һλΪ���ţ���������ɨ�裬�����һ���Ǹ��ţ��滻Ϊ(0-1)*5+2+3*4
	//1+2+3+(-2+4)   �����ڵ�һλΪ���ţ��滻Ϊ1+2+3+((0-1)*2+4)
	//5 * -2 * 5  �滻Ϊ5 * (0-1)*2 * 5
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

	//cout <<"���ʽԤ���������Ϊ��"<<midex<<endl;

	for (int i = midex_len - 1; i >= 0; i--) { //��������ɨ��
		//string midexi(1, midex[i]);  //����ǰ�ַ�תΪstring
		if (midex[i] >= '0' && midex[i] <= '9' || midex[i] == '.') {

			//��Ϊ��������������ѭ����ǰ��ȡѹ����ʱջֱ����һ��������Ϊֹ�������еĲ�����ͨ�����ϳ�һ�������Ķ�λ������С����ѹ��s2������507,3.62����
			//stack<char> num_tmp;
			ostringstream strtmp;  //������������string
			for (int j = i; j >= 0 && (midex[j] >= '0' && midex[j] <= '9' || midex[j] == '.' || midex[j] == ' ' || midex[j] == '\t'); j--, i--) //�Ӻ���ǰ��ȡ��ֱ����һ��������Ϊֹ
			{
				if (midex[j] == ' ' || midex[j] == '\t') //�����������ÿո�
				{
					continue;
				}
				else
					strtmp<<midex[j];
			}
			i++;  //��Ϊfor��������һ����������Ҫ��һ��
			
			string a = strtmp.str();
			string s(a.rbegin(), a.rend()); //�ַ�������
			s2.push(s);  //����������ѹ��s2

		}
		//(1>2)+(2+(3<=5))*4-5%2
		else if (OPS.ops.find(CTS.CharToStr(midex[i])) != OPS.ops.end()) { //��Ϊ����������ж�������ǵ�λ���Ƕ�λ�ģ�Ȼ����s1ջ���������ȼ��Ƚϣ���ǲ���1��
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
					if (s1.empty() || s1.top()[0] == ')') { //��s1Ϊ�ջ���ջ��Ϊ�����ţ��������ջs1
						string str(1, midex[i]);
						s1.push(str);
						break;
					}
					else if (OPS.priority[midexi] >= OPS.priority[s1.top()]) { //����ǰԪ�����ȼ���ջ��Ԫ�ظ߻���ȣ���ջs1
						string str(1, midex[i]);
						s1.push(str);
						break;
					}
					else if (OPS.priority[midexi] < OPS.priority[s1.top()]) { //�����ȼ��ͣ�s1ջ�������ѹ��s2����ջ,Ȼ�������s1ջ��������Ƚϣ��ظ���ǲ���1
						s2.push(s1.top());
						s1.pop();
						continue;
					}
				}
			}
			else
			{
				while (true) {
					if (s1.empty() || s1.top()[0] == ')') { //��s1Ϊ�ջ���ջ��Ϊ�����ţ��������ջs1
						s1.push(b);
						break;
					}
					else if (OPS.priority[b] >= OPS.priority[s1.top()]) { //����ǰԪ�����ȼ���ջ��Ԫ�ظ߻���ȣ���ջs1
						s1.push(b);
						break;
					}
					else if (OPS.priority[b] < OPS.priority[s1.top()]) { //�����ȼ��ͣ�s 1ջ�������ѹ��s2����ջ,Ȼ�������s1ջ��������Ƚϣ��ظ���ǲ���1
						s2.push(s1.top());
						s1.pop();
						continue;
					}
				}
			}
		
		}

		else if (midex[i] == ')') { //����������ֱ��ѹ��s1
			string str(1, midex[i]);
			s1.push(str);
		}

		else if (midex[i] == '(') { //���������ţ����ε���s1ջ����s2������������ֹͣ������һ�����Ŷ���
			while (s1.top()[0] != ')') {
				s2.push(s1.top());
				s1.pop();
			}
			s1.pop();//����������
		}
	}
	//ɨ����ϣ���S1ʣ����������ε���ѹ��S2
	while (!s1.empty()) {
		s2.push(s1.top());
		s1.pop();
	}
	return s2;
}

