#include "PreexParAndEva.h"
#include<stack>
#include<string>
#include "SymbolSetAndPriority.h"
#include "Calculate.h"
#include "CommonStackMethod.h"
using namespace std;



//计算类，传参前缀表达式栈 计算返回结果 默认返回double类型的计算结果 函数内带判断结果是否为逻辑运算的输出
double PreexParAndEva::Cal_Preex(stack<string>& preex) {
	SymbolSetAndPriority OPS;//实例化符号参数方法
	Calculate<double> Cal;
	CommonStackMethod<string> C;//通用栈方法实例化
	stack<double> result;  //初始化一个结果栈
	bool flag=false;//操作符结尾标记符
	preex = C.ReversalStack(preex); //栈逆序
	
	while (!preex.empty()) //开始读取栈内容，判断出栈元素类型，若为数字，转为double类型后入栈result，若为操作符，则取出result栈的俩结果进行运算后存入result栈。
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
				flag = true;  //判断最后取出的操作符是不是逻辑运算的操作符
			}
			else
			{
				flag = false;
			}
			result.push(Cal.cal(n1, n2, op));
		}

	}
	double newresult = result.top(); //最后取出result栈顶元素并返回
	//if (flag)
	//{
	//	cout << "最终运算为逻辑运算，结果为：" << boolalpha << bool(newresult);
	//}
	//else
	//{
	//	cout << "最终运算为数学计算，计算结果为:" <<fixed<< newresult;
	//}
	return newresult;
	
}
