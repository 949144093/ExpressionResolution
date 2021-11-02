#pragma once
#include<iostream>
#include<map>
using namespace std;

template<typename T>
class Calculate
{
public:
	//计算模板声明
	T cal(T n1, T n2, string op);
};

//计算模板
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

	//优化Switch支持string失败，各种方法都试过了，后续再优化
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


