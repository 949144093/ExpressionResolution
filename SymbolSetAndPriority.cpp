#include "SymbolSetAndPriority.h"
set<string> SymbolSetAndPriority::ops = { "+","-","*","/","%",">","<","!","=",">=", "<=", "==", "!=","&&","||","&","|"};//������ż���
map<string, int>SymbolSetAndPriority::priority = { {"+",1},{"-",1},{"*",2},{"/",2},{"%",2} ,{">",0}, {"<",0} ,{">=", 0}, { "<=",0 }, { "==",0 }, { "!=",0 },{ "&&",-1 },{ "||",-1 } };//����������ȼ��ֵ�

SymbolSetAndPriority::SymbolSetAndPriority()
{
}
