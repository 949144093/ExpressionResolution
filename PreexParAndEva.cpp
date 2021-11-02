#include "PreexParAndEva.h"
#include<stack>
#include<string>
#include "SymbolSetAndPriority.h"
#include "Calculate.h"
#include "CommonStackMethod.h"
using namespace std;



//�����࣬����ǰ׺���ʽջ ���㷵�ؽ�� Ĭ�Ϸ���double���͵ļ����� �����ڴ��жϽ���Ƿ�Ϊ�߼���������
double PreexParAndEva::Cal_Preex(stack<string>& preex) {
	SymbolSetAndPriority OPS;//ʵ�������Ų�������
	Calculate<double> Cal;
	CommonStackMethod<string> C;//ͨ��ջ����ʵ����
	stack<double> result;  //��ʼ��һ�����ջ
	bool flag=false;//��������β��Ƿ�
	preex = C.ReversalStack(preex); //ջ����
	
	while (!preex.empty()) //��ʼ��ȡջ���ݣ��жϳ�ջԪ�����ͣ���Ϊ���֣�תΪdouble���ͺ���ջresult����Ϊ����������ȡ��resultջ�������������������resultջ��
	{
		
		if (!(OPS.ops.find(preex.top().c_str()) != OPS.ops.end())) {
			double doubleStr = atof(preex.top().c_str());
			result.push(doubleStr);
			preex.pop();  
		}
		else {
			double n1 = result.top();
			result.pop();
			double n2 = result.top();
			result.pop();
			string op = preex.top();
			preex.pop();
			if (op=="=="||op=="!="||op==">" || op == ">=" || op == "<" || op == "<=" ||op=="&&" || op =="||")
			{
				flag = true;  //�ж����ȡ���Ĳ������ǲ����߼�����Ĳ�����
			}
			else
			{
				flag = false;
			}
			result.push(Cal.cal(n1, n2, op));
		}

	}
	double newresult = result.top(); //���ȡ��resultջ��Ԫ�ز�����
	//if (flag)
	//{
	//	cout << "��������Ϊ�߼����㣬���Ϊ��" << boolalpha << bool(newresult);
	//}
	//else
	//{
	//	cout << "��������Ϊ��ѧ���㣬������Ϊ:" <<fixed<< newresult;
	//}
	return newresult;
	
}
