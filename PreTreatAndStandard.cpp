#include "PreTreatAndStandard.h"
#include <stack>
#include "SymbolSetAndPriority.h"
#include "CharToString.h"
#include "CommonStackMethod.h"
//��׼��Ԥ����    SUM PARAM 4 IPARAM 1   ->   SUM(PARAM[4],IPARAM[1])
//��׼��Ԥ����    SUM SUM 1 IPARAM 1 1  ->   SUM(SUM(1,IPARAM[1],2)
//����˼· ʹ��ջ ��������ɨ������ ���������� �����ջs1 ���������� ��ȡ��һ������ ƴ����������s1 ���������� ���ѯ����������� ��s1 ȡ����Ӧ�����Ĳ�����ƴ�ӷ���s1
//�����Ż� ������SUM 2 3 + SUM 2 3�м���˷���Ҫ��δ���(����ɣ�
string PreTreatAndStandard::InputNormalizationg(string s) {
	stack<string> s1;
	SymbolSetAndPriority OPS;
	CharToString CTS;
	CommonStackMethod<string> C;
	for (int i = s.length()-1; i >=0 ; i--)
	{
		if (isdigit(s[i])||s[i]=='.')
		{
			ostringstream numStr;
			for (int j = i; j >= 0&&(isdigit(s[j])||s[i]=='.'); j--,i--)
			{
				numStr << s[j];
			}
			i++;
			string NumName = numStr.str();
			string NewNumName(NumName.rbegin(), NumName.rend());
			s1.push(NewNumName);
		}
		else if (isalpha(s[i]))
		{
			ostringstream attrStr;
			int EndPos = i;
			for (int j = i; j>=0&&isalpha(s[j]); j--, i--)
			{
				attrStr << s[j];
			}
			i++;
			string AttrName = attrStr.str();
			string NewAttrName(AttrName.rbegin(), AttrName.rend());

			if (NewAttrName == "TIMES" || NewAttrName == "DIV" || NewAttrName == "ADD" || NewAttrName == "SUB")
			{
				//�滻Ϊ��Ӧ����
				string symbol = FunctionParaSettings::SymbolReplace[NewAttrName];
				ostringstream OpsS;
				OpsS << symbol;
				OpsS << s1.top();
				s1.pop();
				s1.push(OpsS.str());

			}

			string AttrType = FunctionParaSettings::FindType[NewAttrName];
			if (AttrType == "Array")
			{
				ostringstream ArrayS;
				ArrayS << NewAttrName + "[" + s1.top() + "]";
				s1.pop();
				s1.push(ArrayS.str());
			}
			else if (AttrType=="Function")
			{
				ostringstream FuncS;
				int AttrNum = FunctionParaSettings::FuncitonPara[NewAttrName+"()"];
				FuncS <<NewAttrName+"(";
				for (int k = 0; k < AttrNum; k++)
				{
					if (k!=AttrNum-1)
					{
						FuncS << s1.top()+",";
						s1.pop();
					}
					else
					{
						FuncS << s1.top();
						s1.pop();
					}	
				}
				FuncS << ")";
				s1.push(FuncS.str());
			}
		}
		else if (OPS.ops.find(CTS.CharToStr(s[i])) != OPS.ops.end()) //���ǲ����� ֱ��ȡ��ջ��Ԫ������
		{
			ostringstream OpsS;
			OpsS << s[i];
			OpsS << s1.top();
			s1.pop();
			s1.push(OpsS.str());
		}
	}
	string str;
	while (!s1.empty())
	{
		str+=s1.top();
		s1.pop();
	}
	return str;
}



//�㷨������ ��������㷨
//string PreTreatAndStandard::InputNormalizationg(string s)
//{
 //   for (int i = 0; i < s.length(); i++)
 //   {   
 //       ostringstream changestr;
 //       if (isalpha(s[i]))
 //       {
 //           for (int j = i; j < s.length()&& isalnum(s[j]); j++,i++)
 //           {
 //               changestr << s[j];
 //           }
 //           string AttrName = changestr.str();
 //          // cout << AttrName << endl;
 //           string AttrType = FunctionParaSettings::FindType[AttrName];
 //          // cout << AttrType << endl;
 //           
 //           //�����ǰ�ַ���Ϊ���� ����ɨ�� ɨ�赽��һ���ո��滻Ϊ"[" �ڶ����ո��滻Ϊ"]"
 //           if (AttrType=="Array")
 //           {
 //               s[i] = '[';
 //               int k;
 //               for (k = i + 1; isalnum(s[k])&&k<s.length(); k++);
 //               
 //               if (k<s.length()-1)
 //               {
 //                   s[k] = ']';
 //                   s.insert(k+1,",");
 //               }
 //               else
 //               {
 // 
 //                   s.insert(k, "]");
 //                   //s.insert(k+1, ")");
 //               }
 //               //cout << AttrName << "[]" << endl;
 //           }
 //           else if (AttrType=="Function")
 //           {
 //               int AttrNum = FunctionParaSettings::FuncitonPara[AttrName + "()"];
 //             /*  cout << AttrName << "()" << endl;
 //               cout << AttrNum << endl;*/
 //               s[i] = '(';
 //               s+= ')';
 //               int k;
 //               for (k = i+1; isdigit(s[k]) && k < s.length(); k++);
 //               if (k < s.length() - 1 && isdigit(s[k-1]))
 //               {
 //                   s[k]=',';
 //               }

 //           }
 //       }
 ///*       if (isdigit(s[i]))
 //       {
 //           int k;
 //           for (k = i; isdigit(s[k]) && k < s.length(); k++);
 //           if (k < s.length() - 1)
 //           {
 //               s.insert(k, ",");
 //           }
 //       }*/
 //       
 //   }
 //   cout << "����Ԥ��������Ϊ:"<<s<<endl;
 //   return s;
//}
