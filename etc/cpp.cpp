#include <iostream>
  using   namespace   std   ;

class test
{
    public: 
        test()
        {
            pts = this;//构造函数中对静态变量赋值 ，必须在类体外初始化 
            cout<<"construction\n"<<endl;
        }
        static test * pts;//静态成员变量在类中仅仅是声明，没有定义，所以要在类的外面定义，实际上是给静态成员变量分配内存
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
