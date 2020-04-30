#include "inline.h"

// 引用(类型+& + 新名称 = 新值), 相当于是一个const指针, 指向的空间不能变, ==> 类型* const --> 指向在定义时确定, 不会变, 从一而终(int* const) --> const的指针
//		而const 类型*const --> 表示内容和指向都不能变(const int* const a = 5;)
// 1. 在指针前加const 指向不变
// 2. 在类型前加const 内容不会

// 引用在定义时必须初始化. 可以改变内容, 但是不能改变指向
// 引用的底层就是通过指针来实现的
// 引用的价值:
//	1. 使用简单(不用取地址, 不用解引用, 编译器帮我们做自动解引用)
//  2. 使用安全(在定义的时候必须初始化, 就没有空引用这种说法(在底层就相当于不会产生空指针), 不会产生解引用异常的问题)
//  3. 想要用const指针的地方 都可以用引用, 
// 引用即别名, 使用方式和普通变量相同, 当原变量来对待 , 
// 底层实现: 通过指针来实现,
void test(){
	int a = 10;
	int b = -1;
	// ra引用, 是变量a的别名, a所代表的空间有两个名字, 代表还是原变量本身
	int& ra = a;

	ra = 20;// a 和 ra 都为 20

	// 引用在定义之后就不会再改变指向了, 始终指向本体
	int& rra = a;
	rra = b; // a变为-1, 修改了值

	// 常引用: 常引用可以指向const变量, 常量, 临时变量
	const int c = 30;
	const int& rc = c;
	//rc = 100;// const引用的内容不能变 --> 常引用
	const int& r1 = 10;

	double d = 2.3;
	ra = d;// a = 2
	double& rd = d;
	// int& rd2 = d;// 类型不一致
	const int& rd2 = d;// 发生了隐式类型转换 生成了一个int的临时变量2, 这里的rd2不是d(double)的别名, 指向的是一个临时变量, 不是d, 因为临时变量具有常性, 

	int* pa = &a;
	//const int& rpa = pa;// 当两个类型不支持隐式类型转换时 加了const也不行

} 

// 交换两个数值的内容
void Swap(int* array, int i, int j){ // Swap(array, 2, 3) i和j相当于是地址, 索引 传的是数组
	int tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}
// 不仅传地址, 还传值, 
void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
// 引用做参数
// 这里的a, b为局部变量, 但是指向的是外部的本体, 局部变量交换内容也就相当于本体交换了
// 底部实现其实和swap是一样的(传指针一样) , 都是先取地址, 但是和上面不同的是引用只传地址, 没有传内容(值),所以快
void swap2(int& a, int& b){
	int tmp = a;
	a = b;
	b = a;
}
void test2(){
	int a = 10;
	int b = 20;

	swap(&a, &b);
	swap2(a, b);
}

// 引用做返回值(不能返回临时变量(不能反悔生命周期小于函数生命周期的变量)
int& Add(int& ra){
	return ++ra;
}
int& Add(int a, int b){
	int c = a + b;
	return c; // c为一局部变量, Add栈帧调用完了 之后就销毁了, 下一次再调其他的函数, ret指的就不是c了
}
void test3(){
	int a = 10;
	int& ra = Add(a);// 11
	ra += 10;// 21
}



void test4(){
	int a = 1;
	int b = 2;
	int& ret = Add(a, b);// 3 调用完函数栈帧销毁, 空间内容不受保护
	Add(10, 20);// 30       其他函数应用这片区域,  
	cout << "test4()" << endl;
}
int main1(){

	test4();
	//test3();
	//test2();
	//test();

	system("pause");
	return 0;
}

// 传参
struct A{
	int array[100000];
};
A globalA;// 全局变量
// 传值(每调一次 拷贝一次)
void funVal(A a){};
// 传引用(没有发生拷贝的过程) 一个引用及时一个变量的别名 是本身(不需要拷贝)
void funRef(A& a){};
void test5(){
	//  参数传引用比传值效率高, 传引用没有拷贝发生
	size_t begin = clock();
	for (int i = 0; i < 100000; ++i)
		funVal(globalA);
	size_t end = clock();
	cout << "funVal:" << end - begin << endl;

	begin = clock();
	for (int i = 0; i < 100000; ++i)
		funRef(globalA);
	end = clock();
	cout << "funRef:" << end - begin << endl;
}

// 返回值
A funVal2(){
	return globalA;
}
A funRef2(){
	return globalA;
}
void test61(){
	// 返回引用比返回值效率高, 返回引用没有拷贝发生
	size_t begin = clock();
	for (int i = 0; i < 100000; ++i)
		funVal2();
	size_t end = clock();
	cout << "funVal2:" << end - begin << endl;

	begin = clock();
	for (int i = 0; i < 100000; ++i)
		funRef2();
	end = clock();
	cout << "funRef2:" << end - begin << endl;
}
// 引用的底层就是指针, 通过指针实现引用
void test6(){
	int a = 10;
	int* pa = &a;
	*pa = 20;

	int b = 1;
	int& rb = b;
	rb = 2;
}

// 对引用操作就是对本体操作, 对copy操作不会影响本体
struct B{
	int _a;
	int _b;
	int _c;
};
void test7(){
	B b; // 结构体变量
	B& rb = b;// &b 和 &rb 的值是一样的
	B* pb = &b;
	B copy = b;// 结构体的副本, 克隆(双胞胎) &copy值和&b不一样 另一个空间

	b._a = 10;
	rb._a = 20;// 编译器在底层会翻译成指针的操作 rb->_a = 20
	pb->_a = 40;// 这三个改的都是同一个空间的内容

	// 这是另外一个新的空间
	copy._a = 30;// 只影响copy中的内容, 不会影响b的内容

	// rb->_a = 10; 错的
}

void test8(){
	// 指针和引用的区别, 
	// 1. 引用在定义时必须初始化, 指针可以不用初始化, 
	int a = 10;
	int& ra = a;
	int* pa;
	// 2. 只有一级引用, 没有多级引用, 指针可以有多级指针
	int& ra2 = a;
	int** pa2 = &pa;
	int*** pa3 = &pa2;
	// 3. 引用的自加是实体内容自加, 而指针自加是地址的偏移
	ra++; // a的内容加1
	pa++; // 向后偏移4个字节的空间
	// 4. sizeof(引用)表实体的大小, sizeof(指针)表示指针的大小
	B b;
	B& rb = b;
	B* pb = &b;
	cout << "引用大小:" << sizeof(rb) << endl;// 求b的大小 = 12
	cout << "指针大小:" << sizeof(pb) << endl;// 求指针的大小 = 4

	// 5. 有空指针 , 但是没有空引用
	//int& ra3 = NULL; 
	int* pc = NULL;
	// 6. 引用更加安全, 不会有空异常

}
int main3(){
	test8();

	// test5();

	system("pause");
	return 0;
}

