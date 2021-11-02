#include "SymbolSetAndPriority.h"
set<string> SymbolSetAndPriority::ops = { "+","-","*","/","%",">","<","!","=",">=", "<=", "==", "!=","&&","||","&","|"};//定义符号集合
map<string, int>SymbolSetAndPriority::priority = { {"+",1},{"-",1},{"*",2},{"/",2},{"%",2} ,{">",0}, {"<",0} ,{">=", 0}, { "<=",0 }, { "==",0 }, { "!=",0 },{ "&&",-1 },{ "||",-1 } };//定义符号优先级字典

SymbolSetAndPriority::SymbolSetAndPriority()
{
}
