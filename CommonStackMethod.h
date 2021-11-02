#pragma once
#include<iostream>
#include<stack>
#include<sstream>
#include<string>
using namespace std;
//栈通用操作类 使用T类型模板实现
template<typename T>
class CommonStackMethod
{
public:
	CommonStackMethod();
	~CommonStackMethod();
	//声明通用输出栈方法
	void PutStack(stack<T> s);
	//声明通用栈逆置模板
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

//实现通用输出栈方法
template<typename T>
void CommonStackMethod<T>::PutStack(stack<T> s) {
	while (!s.empty()) {
		//cout << s.top() << " ";
		s.pop();
	}
	//cout << endl;
}
//实现通用栈逆置模板
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

