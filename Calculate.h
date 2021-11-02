#pragma once
#include<iostream>
#include<map>
using namespace std;

template<typename T>
class Calculate
{
public:
	//����ģ������
	T cal(T n1, T n2, string op);
};

//����ģ��
template<typename T>
T Calculate<T>::cal(T n1, T n2, string op) {
	T res;
	if (op=="+")
	{
		res = n1 + n2;
	}
	else if(op=="-")
	{
		res = n1 - n2;
	}
	else if (op=="*")
	{
		res = n1 * n2;
	}
	else if (op == "/")
	{
		res = n1 / n2;
	}
	else if (op == "%")
	{
		res = int(n1) % int(n2);
	}
	else if (op == ">")
	{
		res = int(n1 > n2);
	}
	else if (op == "<")
	{
		res = int(n1 < n2);
	}
	else if (op == ">=")
	{
		res = int(n1 >= n2);
	}
	else if (op == "<=")
	{
		res = int(n1 <= n2);
	}
	else if (op == "!=")
	{
		res = int(n1 != n2);
	}
	else if (op == "==")
	{
		res = int(n1 == n2);
	}
	else if (op == "&&")
	{
		res = int(n1 && n2);
	}
	else if (op == "||")
	{
		res = int(n1 || n2);
	}
	return res;

	//�Ż�Switch֧��stringʧ�ܣ����ַ������Թ��ˣ��������Ż�
	/*switch (op) {
	case switch_hash("+"):
		res = n1 + n2;
		break;
	case switch_hash("-"):
		res = n1 - n2;
		break;
	case switch_hash("*"):
		res = n1 * n2;
		break;
	case switch_hash("/"):
		res = n1 / n2;
		break;
	case switch_hash("%"):
		res = int(n1) % int(n2);
		break;
	case switch_hash(">"):
		res = int(n1 > n2);
		break;
	case switch_hash("<"):
		res = int(n1 < n2);
		break;
	case switch_hash(">="):
		res = int(n1 >= n2);
		break;
	default:
		break;
	}*/
	
}


