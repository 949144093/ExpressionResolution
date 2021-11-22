// expressionResolution.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
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



//������main��ڣ����е��÷��������Է����ȵ�
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
	//���������������(string����)

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
	�������� 
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
	֧�ֳ����쳣���봦��
	�����ַ�
	��������
	ֱ�ӻس�
	��Ч�ո�
	sss
	aaa
	bbb

	֧��
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


	////ʵ�ֻ���һλ���������Ӽ��˳���׺תǰ׺
	//cout << "ʵ�ֻ���һλ�����Ӽ��˳���׺תǰ׺�Լ�����"<<endl;
	//string a = "1+(2+3)*4-5";
	//cout << "��׺���ʽΪ:" << a << endl;
	//cout << "��Ӧǰ׺���ʽΪ:";
	//stack<string> s1 = M.MiddleexToPrevex(a);
	//C.PutStack(s1);//- + 1 * + 2 3 4 5
	//P.Cal_Preex(s1);
	//cout << "\n-------------------------\n";

	////ʵ�ֻ�����λ���������Ӽ��˳���׺תǰ׺��֧�ְ����ո�
	//cout << "ʵ�ֶ�λ���������Ӽ��˳���׺תǰ׺��֧�ְ����ո�" << endl;
	//string b = "1 + ( 2 + 301 ) * 4 - 5";
	//cout << "��׺���ʽΪ:" << b << endl;
	//cout << "��Ӧǰ׺���ʽΪ:";
	//stack<string> s2 = M.MiddleexToPrevex(b);
	//C.PutStack(s2);//- + 1 * + 2 301 4 5
	//P.Cal_Preex(s2);
	//cout << "\n-------------------------\n";

	////ʵ�ְ���С�������Ӽ��˳���׺תǰ׺
	//cout << "ʵ�ְ���С�������Ӽ��˳���׺תǰ׺" << endl;
	//string c = "1.7+(2+4.3)*4.7-502";
	//cout << "��׺���ʽΪ:" << c << endl;
	//cout << "��Ӧǰ׺���ʽΪ:";
	//stack<string> s3 = M.MiddleexToPrevex(c);
	//C.PutStack(s3);//- + 1.7 * + 2 4.3 4.7 502
	//P.Cal_Preex(s3);
	//cout << "\n-------------------------\n";

	////ʵ��֧�ֺ���������׺ת��׺ ������֧������
	//cout << "ϣ��ʵ��֧�ֺ���������׺ת��׺ ������֧������" << endl;
	//string d = "max(abs(RANDOM(-90,-10)),RANDOM(1,9))";
	//cout << "��׺���ʽΪ:" << d << endl;
	//cout << "��Ӧ��׺���ʽΪ:";
	//stack<string> s4 = F.FuncExpression(d);
	//C.PutStack(s4);
	//cout << "-------------------------\n";
	////��Ҫ�������������׺���ʽ  total_house = eval(response.xpath('//*[@id="beike"]/div[1]/div[4]/div[1]/div[2]/div[1]/h2/span/text()').extract()[0])

	////ʵ��֧�ֺ���������׺ת��׺ ����֧������
	//cout << "ʵ��֧�ֺ���������׺ת��׺ ����֧������" << endl;
	//string e = "max(abs(RANDOM(func1,-10)),RANDOM(1,func2))";
	//cout << "��׺���ʽΪ:" << e << endl;
	//cout << "��Ӧ��׺���ʽΪ:";
	//stack<string> s5 = F.FuncExpression(e);
	//C.PutStack(s5);
	//cout << "-------------------------\n";
	////��Ҫ�������������׺���ʽ func1 -10 RANDOM () abs () 1 func2 RANDOM () max ()

	////������ȡ�����,�߼����ڣ��߼�С�ڣ��ǵü������ţ����������쳣���
	//cout << "������ȡ�����,�߼����ڣ��߼�С�ڣ��߼�������������ţ��������ִ���߼����㷵��True����False" << endl;
	//string f = "(1>2)+(2+(3<5))*4-5%2";
	//cout << "��׺���ʽΪ:" << f << endl;
	//cout << "��Ӧǰ׺���ʽΪ:";
	//stack<string> s6 = M.MiddleexToPrevex(f);
	//C.PutStack(s6);
	//P.Cal_Preex(s6);
	//cout << "\n-------------------------\n";

	////�����˶�λ���ŵ��߼����㣬�߼����ڵ��ڣ�С�ڵ��ڣ������ڣ����ڵ���
	//cout << "��չ�˶�λ���ŵ��߼����㣬�߼����ڵ��ڣ�С�ڵ��ڣ������ڣ����ڵ��ڣ���չ�˷�����֧�ֵ�����" << endl;
	//string g = "(1>2)+(2+(3<=5))*4-5%2+(1!=2)+2==14";
	//cout << "��׺���ʽΪ:" << g << endl;
	//cout << "��Ӧǰ׺���ʽΪ:";
	//stack<string> s7 = M.MiddleexToPrevex(g);
	//C.PutStack(s7);
	//P.Cal_Preex(s7);
	//cout << "\n-------------------------\n";


	return 0;
}

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���:
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�



