#include "inline.h"

// ����(����+& + ������ = ��ֵ), �൱����һ��constָ��, ָ��Ŀռ䲻�ܱ�, ==> ����* const --> ָ���ڶ���ʱȷ��, �����, ��һ����(int* const) --> const��ָ��
//		��const ����*const --> ��ʾ���ݺ�ָ�򶼲��ܱ�(const int* const a = 5;)
// 1. ��ָ��ǰ��const ָ�򲻱�
// 2. ������ǰ��const ���ݲ���

// �����ڶ���ʱ�����ʼ��. ���Ըı�����, ���ǲ��ܸı�ָ��
// ���õĵײ����ͨ��ָ����ʵ�ֵ�
// ���õļ�ֵ:
//	1. ʹ�ü�(����ȡ��ַ, ���ý�����, ���������������Զ�������)
//  2. ʹ�ð�ȫ(�ڶ����ʱ������ʼ��, ��û�п���������˵��(�ڵײ���൱�ڲ��������ָ��), ��������������쳣������)
//  3. ��Ҫ��constָ��ĵط� ������������, 
// ���ü�����, ʹ�÷�ʽ����ͨ������ͬ, ��ԭ�������Դ� , 
// �ײ�ʵ��: ͨ��ָ����ʵ��,
void test(){
	int a = 10;
	int b = -1;
	// ra����, �Ǳ���a�ı���, a������Ŀռ�����������, ������ԭ��������
	int& ra = a;

	ra = 20;// a �� ra ��Ϊ 20

	// �����ڶ���֮��Ͳ����ٸı�ָ����, ʼ��ָ����
	int& rra = a;
	rra = b; // a��Ϊ-1, �޸���ֵ

	// ������: �����ÿ���ָ��const����, ����, ��ʱ����
	const int c = 30;
	const int& rc = c;
	//rc = 100;// const���õ����ݲ��ܱ� --> ������
	const int& r1 = 10;

	double d = 2.3;
	ra = d;// a = 2
	double& rd = d;
	// int& rd2 = d;// ���Ͳ�һ��
	const int& rd2 = d;// ��������ʽ����ת�� ������һ��int����ʱ����2, �����rd2����d(double)�ı���, ָ�����һ����ʱ����, ����d, ��Ϊ��ʱ�������г���, 

	int* pa = &a;
	//const int& rpa = pa;// ���������Ͳ�֧����ʽ����ת��ʱ ����constҲ����

} 

// ����������ֵ������
void Swap(int* array, int i, int j){ // Swap(array, 2, 3) i��j�൱���ǵ�ַ, ���� ����������
	int tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}
// ��������ַ, ����ֵ, 
void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
// ����������
// �����a, bΪ�ֲ�����, ����ָ������ⲿ�ı���, �ֲ�������������Ҳ���൱�ڱ��彻����
// �ײ�ʵ����ʵ��swap��һ����(��ָ��һ��) , ������ȡ��ַ, ���Ǻ����治ͬ��������ֻ����ַ, û�д�����(ֵ),���Կ�
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

// ����������ֵ(���ܷ�����ʱ����(���ܷ�����������С�ں����������ڵı���)
int& Add(int& ra){
	return ++ra;
}
int& Add(int a, int b){
	int c = a + b;
	return c; // cΪһ�ֲ�����, Addջ֡�������� ֮���������, ��һ���ٵ������ĺ���, retָ�ľͲ���c��
}
void test3(){
	int a = 10;
	int& ra = Add(a);// 11
	ra += 10;// 21
}



void test4(){
	int a = 1;
	int b = 2;
	int& ret = Add(a, b);// 3 �����꺯��ջ֡����, �ռ����ݲ��ܱ���
	Add(10, 20);// 30       ��������Ӧ����Ƭ����,  
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

// ����
struct A{
	int array[100000];
};
A globalA;// ȫ�ֱ���
// ��ֵ(ÿ��һ�� ����һ��)
void funVal(A a){};
// ������(û�з��������Ĺ���) һ�����ü�ʱһ�������ı��� �Ǳ���(����Ҫ����)
void funRef(A& a){};
void test5(){
	//  ���������ñȴ�ֵЧ�ʸ�, ������û�п�������
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

// ����ֵ
A funVal2(){
	return globalA;
}
A funRef2(){
	return globalA;
}
void test61(){
	// �������ñȷ���ֵЧ�ʸ�, ��������û�п�������
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
// ���õĵײ����ָ��, ͨ��ָ��ʵ������
void test6(){
	int a = 10;
	int* pa = &a;
	*pa = 20;

	int b = 1;
	int& rb = b;
	rb = 2;
}

// �����ò������ǶԱ������, ��copy��������Ӱ�챾��
struct B{
	int _a;
	int _b;
	int _c;
};
void test7(){
	B b; // �ṹ�����
	B& rb = b;// &b �� &rb ��ֵ��һ����
	B* pb = &b;
	B copy = b;// �ṹ��ĸ���, ��¡(˫��̥) &copyֵ��&b��һ�� ��һ���ռ�

	b._a = 10;
	rb._a = 20;// �������ڵײ�ᷭ���ָ��Ĳ��� rb->_a = 20
	pb->_a = 40;// �������ĵĶ���ͬһ���ռ������

	// ��������һ���µĿռ�
	copy._a = 30;// ֻӰ��copy�е�����, ����Ӱ��b������

	// rb->_a = 10; ���
}

void test8(){
	// ָ������õ�����, 
	// 1. �����ڶ���ʱ�����ʼ��, ָ����Բ��ó�ʼ��, 
	int a = 10;
	int& ra = a;
	int* pa;
	// 2. ֻ��һ������, û�ж༶����, ָ������ж༶ָ��
	int& ra2 = a;
	int** pa2 = &pa;
	int*** pa3 = &pa2;
	// 3. ���õ��Լ���ʵ�������Լ�, ��ָ���Լ��ǵ�ַ��ƫ��
	ra++; // a�����ݼ�1
	pa++; // ���ƫ��4���ֽڵĿռ�
	// 4. sizeof(����)��ʵ��Ĵ�С, sizeof(ָ��)��ʾָ��Ĵ�С
	B b;
	B& rb = b;
	B* pb = &b;
	cout << "���ô�С:" << sizeof(rb) << endl;// ��b�Ĵ�С = 12
	cout << "ָ���С:" << sizeof(pb) << endl;// ��ָ��Ĵ�С = 4

	// 5. �п�ָ�� , ����û�п�����
	//int& ra3 = NULL; 
	int* pc = NULL;
	// 6. ���ø��Ӱ�ȫ, �����п��쳣

}
int main3(){
	test8();

	// test5();

	system("pause");
	return 0;
}

