#include <iostream>
  using   namespace   std   ;

class test
{
    public: 
        test()
        {
            pts = this;//���캯���жԾ�̬������ֵ ���������������ʼ�� 
            cout<<"construction\n"<<endl;
        }
        static test * pts;//��̬��Ա���������н�����������û�ж��壬����Ҫ��������涨�壬ʵ�����Ǹ���̬��Ա���������ڴ�
        #if 1
        int a;
        char b;
        void print(void);
        void f(void);
        test * get(void);
        #endif
 }; 
class test t;
test * test::pts=NULL;

 test * test::get()
 {
     return pts;
 }
 void test::print()
 {
     a=100;
     cout<<"hello"<<endl ;
     get()->f();
 }
 void test::f()
 {
     cout<<"this is functiongggg f\n"<<endl;     
 }
 
int main(int argc, char** argv) {

	t.print();
    
    return 0;
}
