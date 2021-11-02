#pragma once
#include<iostream>
#include<stack>
#include<sstream>
#include<string>
using namespace std;
//ջͨ�ò����� ʹ��T����ģ��ʵ��
template<typename T>
class CommonStackMethod
{
public:
	CommonStackMethod();
	~CommonStackMethod();
	//����ͨ�����ջ����
	void PutStack(stack<T> s);
	//����ͨ��ջ����ģ��
	stack<T> ReversalStack(stack<T> s);
};


template<typename T>
inline CommonStackMethod<T>::CommonStackMethod()
{
}

template<typename T>
inline CommonStackMethod<T>::~CommonStackMethod()
{
}

//ʵ��ͨ�����ջ����
template<typename T>
void CommonStackMethod<T>::PutStack(stack<T> s) {
	while (!s.empty()) {
		//cout << s.top() << " ";
		s.pop();
	}
	//cout << endl;
}
//ʵ��ͨ��ջ����ģ��
template<typename T>
stack<T> CommonStackMethod<T>::ReversalStack(stack<T> s) {
	stack<T> temStack;
	while (!s.empty())
	{
		temStack.push(s.top());
		s.pop();
	}
	return temStack;
}

