#include "inline.h"

/* 内联函数: inline + 普通函数定义
	在编译阶段展开
	1. 对于简单的函数, 会在调用的地方吧指令原地展开,最终在执行时, 没有栈帧开销, 提高代码效率
	2. 对于复杂函数, 即使声明成内联函数, 编译器也不会展开(会消耗太多), 包含循环, 递归...
	3. 可以用内联函数代替宏函数
	4. 内联函数不支持分离定义

替代宏:
	1. 常量定义, 使用const
	2. 函数定义, 使用内联函数inline
	*/

#define F(X, Y) X / Y   // 宏函数 -- >预处理时有宏替换, 
void test9(){
	int ret = F(9, 3);
	int a = 2;
	int b = 4;
	int c = 2;
	ret = F(a + b, c);

}
inline int dev(int x, int y){
	return x / y;
}

// inline适合简单的函数展开, 不适合复杂的(复杂的不会展开)
inline int Fab(int n){
	if (n <= 0)
		return 0;
	if (n == 1 || n == 2)
		return 1;
	return Fab(n - 1) + Fab(n - 2);

}
void test10(){
	int a = 9;
	int b = 3;

	int ret = a / b;

	ret = dev(9, 3); // 实际执行时就是ret = 9 / 3,提高效率 没有函数栈帧开销, inline的作用就是指令原地展开, 比宏函数(没有语法检查, 直接替换)好,

	ret = Fab(40);// 不会展开

}

int main4(){
	test10();

	system("pause");
	return 0;
}

// 在定义内联函数时 最好在.h头文件里就把其定义好, 声明和定义放在同一个地方, 
void test11(){
	int a = 4;
	int b = 2;
	//int ret = sub(4, 2); // 如果将内联函数和其头文件分开,因为其是展开的, 所以没有函数名, 头文件里没有对应的函数体, 所以也不会去找头文件, 导致声明和定义分开
	cout << "ret = " << sub(4, 2) << endl;
}
int main(){
	test11();

	system("pause");
	return 0;
}