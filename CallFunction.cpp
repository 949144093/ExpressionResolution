#include "CallFunction.h"
#include "PreTreatAndStandard.h"
#include<windows.h>
#include<cstdio> 
#include<string>
#include<algorithm>
//void ShowTitle() {
//	cout << "-------------------------------------------------------------------" << endl;
//	cout << "C++���ʽ��������֧��������С���������㣬�߼����㣬��������˳�����" << endl;
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
	//MessageBox(NULL, "�Ի������", "���Ա���", MB_OK);
	a = expressionStrng;
	if (a == "\n" || a == " " || a == "\t" || a == "")
	{
		return 0;
	}

	
	bool valid = true;
	for (int i = 0; i < a.length(); i++)
	{
		//�������ȫ���ַ�
		if (!(a[i] >= 0 && a[i] <= 127)) {
			valid = false;
			break;
		}
	}
	if (!valid)//����ַ����Ϸ�����ʾ������������
	{
		//cout << "�﷨���������Ƿ������������ַ���������������" << endl;
		string ErrorInfo = "�﷨���������Ƿ������������ַ���������������!\n���ִ���ı��ʽΪ:";
		ErrorInfo.append(a);
		MessageBox(NULL, ErrorInfo.c_str(), "Error", MB_OK);
		return 0;
	}

	//��ʼԤ���� �ж��Ƿ�Ҫ�����﷨ת�� ���罫SUM PARAM 4 IPARAM 1   ->   SUM(PARAM[4],IPARAM[1])
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
				//cout << "������﷨ת��Ԥ����" << endl;
				string WariningInfo = "�������﷨ת��Ԥ������������麯�����ú��Ƿ����˿ո�\n���ִ���ı��ʽΪ:";
				WariningInfo.append(a);
				MessageBox(NULL, WariningInfo.c_str(), "Warning", MB_OK);
				a = PTAS.InputNormalizationg(a);
				break;
			}
		}
	}
	//��ʼ�ж�����������Ƿ�ƥ��

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
		//cout << "���Ų�ƥ�䣬�����������" << endl;
		string ErrorInfo = "���Ų�ƥ�䣬�����������!\n���ִ���ı��ʽΪ:";
		ErrorInfo.append(a);
		MessageBox(NULL, ErrorInfo.c_str(), "Error", MB_OK);
		return 0;
	}




	//cout << "��׺���ʽΪ:" << a << endl;
	stack<string> s = M.MiddleexToPrevex(a);
	//cout << "��Ӧǰ׺���ʽΪ:";
	C.PutStack(s);
	double value=P.Cal_Preex(s);
	//cout << "\n-------------------------\n";
	return value;


	//ShowTitle();
	////ʵ�� �쳣�ַ�ʶ�� ��������ͺ��������Զ��жϲ����ö�Ӧ�ӿ�
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
				//�������ȫ���ַ�
				if (!(a[i] >= 0 && a[i] <= 127)) {
					valid = false;
					break;
				}
			}
			if (!valid)//����ַ����Ϸ�����ʾ������������
			{
				cout << "�﷨���������Ƿ������������ַ���������������" << endl;
				continue;
			}

			//��ʼԤ���� �ж��Ƿ�Ҫ�����﷨ת�� ���罫SUM PARAM 4 IPARAM 1   ->   SUM(PARAM[4],IPARAM[1])
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
						cout << "������﷨ת��Ԥ����"<<endl;
						a = PTAS.InputNormalizationg(a);
						break;
					}
				}
			}
			//��ʼ�ж�����������Ƿ�ƥ��

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
				cout << "���Ų�ƥ�䣬�����������" << endl;
				continue;
			}




			cout << "��׺���ʽΪ:" << a << endl;
			stack<string> s = M.MiddleexToPrevex(a);
			cout << "��Ӧǰ׺���ʽΪ:";
			C.PutStack(s);
			P.Cal_Preex(s);
			cout << "\n-------------------------\n";
			*/

	//		//(PARA[1]/2-PARA[4]-(PARA[2]/2-PARA[3]/2)/2*TAN(8))
	//		//if (flag2)
	//		////if(flag1)
	//		//{
	//		//	cout << "��׺���ʽΪ:" << a << endl;
	//		//	cout << "���ʽΪ�������ý���" << endl;
	//		//	cout << "��Ӧ��׺���ʽΪ:";
	//		//	stack<string> s = F.FuncExpression(a);
	//		//	C.PutStack(s);
	//		//	//cout << "�����������:" << endl;
	//		//	cout <<"���ռ�����Ϊ:"<< SFE.SuffixFuncEva(s) << endl;
	//		//	cout << "-------------------------\n";
	//		//}
	//		//else
	//		//{
	//		//	cout << "��׺���ʽΪ:" << a << endl;
	//		//	cout << "���ʽΪ������������߼�����" << endl;
	//		//	cout << "��Ӧǰ׺���ʽΪ:";
	//		//	stack<string> s = M.MiddleexToPrevex(a);
	//		//	C.PutStack(s);
	//		//	P.Cal_Preex(s);
	//		//	cout << "\n-------------------------\n";
	//		//}


	//}
}
