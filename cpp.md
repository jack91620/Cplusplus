# cpp

## 不带指针的类

这是complex类的声明
```c++
class complex
{
public:
    complex(double r = 0, double i = 0)
        : re (r), im (i)
    {}
    complex& operator += (const complex&);
    double real () const {return re;}
    double image () const {return im;}
private:
    double re, im;
    friend complex& __doapl (complex*, const complex&);
};
```
public中的内容外部可以访问，private中的内容外部不能访问，这里数据re, im是外部不能访问的
以下操作是合法的
```c++
complex c1(1, 2);
cout << c1.real();
cout << c1.image();
```
以下操作是非法的
```c++
complex c1(1, 2);
cout << c1.re;
cout << c1.im;
```

## 构造函数
构造函数是将类初始化成对象时自动调用的初始化函数
```c++
    complex(double r = 0, double i = 0)
        : re (r), im (i)
    {}
```
这里，double r = 0, double i = 0表示两个实参的默认参数为0
**所有的函数都可以用默认的实参**
*: re (r), im (i)* 这是initialization list初始化列，只有构造函数有这个语法，表示将r初始化给re，将i初始化给im
```c++
    complex(double r = 0, double i = 0)
    {
        re = r;
        im = i;
    }
```
这样也能初始化re, im，但是效率低，这种写法是在创建对象后，进行的操作，上面的写法是初始化时的操作

**构造函数重载**
构造函数可以有不止1个，如果希望以不同的方式初始化出1个对象，就可以用不同的构造函数

不可以使用的构造函数重载
```c++
class complex
{
public:
    complex(double r = 0, double i = 0)
        : re (r), im (i)
    {}
    complex() : re(0), im(0){}

    complex& operator += (const complex&);
    double real () const {return re;}
    double image () const {return im;}
private:
    double re, im;
    friend complex& __doapl (complex*, const complex&);
};
```
因为第一个构造函数有默认参数，用complex c1();或者complex c2;初始化一个对象时，编译器不知道用哪个构造函数来初始化
不同的构造函数之间不能有冲突

## 内联函数
```c++
    double real () const {return re;}
    double image () const {return im;}
```
这两个函数在class body中完成了函数的定义，自动成为inline的候选人，编译器会优先将这些函数内联

## class模板
```c++
template<typename T>
class complex
{
public:
    complex(double r = 0, double i = 0)
        : re (r), im (i)
    {}
    complex& operator += (const complex&);
    double real () const {return re;}
    double image () const {return im;}
private:
    T re, im;
    friend complex& __doapl (complex*, const complex&);
};

{
    complex<double> c1(2.5, 1.5);
    complex<int> c2(2, 6);
}
```
这里，数据的类型作为模板，可以在创建类的实例时制定数据的类型

## 函数的重载
```c++
class complex
{
public:
    complex(double r = 0, double i = 0)
        : re (r), im (i)
    {}
    complex& operator += (const complex&);
    double real () const {return re;}
    double image () const {return im;}
private:
    double re, im;
    friend complex& __doapl (complex*, const complex&);
};

void real(double r) {re = r};
```
这里重写了函数real

## 放在private区的构造函数
构造函数一般不允许放在private区
singleton的设计模式允许将构造函数放在private区
```c++
class A {
public:
    static A& getInstance();
    setup() { ... }
private:
    A();
    A(const A& rhs);
...
};

A& A::getInstance()
{
    static A a;
    return a;
}
```

## 常量成员函数
```c++
class complex
{
public:
    complex(double r = 0, double i = 0)
        : re (r), im (i)
    {}
    complex& operator += (const complex&);
    double real () const {return re;}
    double image () const {return im;}
private:
    double re, im;
    friend complex& __doapl (complex*, const complex&);
};
```
这里real()，image()是两个常量成员函数，不改变类的数据
如果成员函数需要改变类的数据，就不加const标记

## 参数传递与返回值
尽量使用引用来传递参数（相当于C中的指针）
尽量使用引用作为函数的返回值
```c++
complex(double r = 0, double i = 0)
        : re (r), im (i)
    {}
```
这里用值传递参数
```c++
complex& operator += (const complex&);
```
这里用引用传递参数，而且函数不允许修改这个参数

## 友元函数
```c++
class complex
{
public:
    complex(double r = 0, double i = 0)
        : re (r), im (i)
    {}
    complex& operator += (const complex&);
    double real () const {return re;}
    double image () const {return im;}
private:
    double re, im;
    friend complex& __doapl (complex*, const complex&);
};

inline friend complex& __doapl(complex* ths, const complex& r)
{
    ths->re += r.re;
    ths->im += r.im;
}
```
友元函数可以自用取得类的数据
这里__doapl是complex类的1个友元函数，返回值类型是引用complex&

一个class下面定义的各个object（函数？？）互为友元函数，都可以自由获取类的数据

因此，下面的操作是OK的
```c++
class complex
{ 
public:
    complex (double r = 0, double i = 0)
        : re (r), im (i)
    { }
    int func(const complex& param)
    { return param.re + param.im; }
private:
    double re, im;
};

complex c1(2, 1);
complex c2;
c2.function(c1);
```

## 操作符重载

```c++
{
    complex c1(2,1);
    complex c2(5);

    c1 += c2;
}
```

对于编译器来说，看到对c1的+=操作，看c1这个类有没有对+=的操作符重载函数


### 成员函数
```c++
class complex
{
public:
    complex(double r = 0, double i = 0)
        : re (r), im (i)
    {}
    complex& operator += (const complex&);
    double real () const {return re;}
    double image () const {return im;}
private:
    double re, im;
    friend complex& __doapl (complex*, const complex&);
};
```
对于成员函数，自带参数this，是reference，指向调用者，相当于这样
```c++
inline complex& complex::operator += (this, const complex& r)
{
    return __doapl (this, r);
}
```
这是真实的实现
complex::operator += 表明+=是complex类的成员函数
__doapl是全局函数
```c++
inline complex& complex::operator += (const complex& r)
{
    return __doapl (this, r);
}

inline complex& __doapl (complex* ths, const complex& r)
{
    // ths是指针
    ths->re += r.re;
    ths->im += r.im;
    return *ths;
    // 返回的是值，函数声明需要返回reference
}
```
pointer和reference的区别：
调用函数的调用者无需知道被调用者是否以reference接受参数
无论函数的参数设计成值或者reference，调用者都可以传值
函数的返回也不用知道函数是否以reference返回，都可以直接返回值

对于
```c++
{
    complex c1(2,1);
    complex c2(5);

    c1 += c2;
}
```
这样的用法，complex::operator也没必要返回complex&，因为是对this做操作，但是如果有下面的用法
```c++
{
    complex c1(2,1);
    complex c2(5);
    complex c3(4);

    c1 += c2 += c3;
}
```
### 非成员函数

```c++
class complex
{
public:
    complex(double r = 0, double i = 0)
        : re (r), im (i)
    {}
    complex& operator += (const complex&);
    double real () const {return re;}
    double image () const {return im;}
private:
    double re, im;
    friend complex& __doapl (complex*, const complex&);
};

inline complex& __doapl (complex* ths, const complex& r)
{
    // ths是指针
    ths->re += r.re;
    ths->im += r.im;
    return *ths;
    // 返回的是值，函数声明需要返回reference
}

inline complex& complex::operator += (const complex& r)
{
    return __doapl (this, r);
}

inline double imag(const complex& x)
{
    return x.imag();
}

inline double real(const complex& x)
{
    return x.real();
}
// 复数加法的操作符重载
// 因为+操作可能对左值不是complex类型的值操作，所以不能设计为成员函数
inline complex operator + (const complex& x, const complex& y)
{
    return complex(real(x) + real(y), imag(x) + imag(y));
}

inline complex operator + (const complex& x, double y)
{
    return complex(real(x) + y, imag(x));
}

inline complex operator + (double x, const complex& y)
{
    return complex(x, + real(y), imag(y));
}

inline complex operator + (const complex& x)
{
    return x;
}
// 这里其实可以返回reference

inline complex operator - (const complex& x)
{
    return complex(-real(x), -imag(x));
}
// 这里一定不能返回reference，因为肯定是个值

inline bool operator == (const complex& x, const complex& y)
{
    return real(x) == real(y) && imag(x) == imag(y);
}

inline bool operator == (const complex& x, double y)
{
    return real(x) == y && imag(x) == 0;
}

inline bool operator == (double x, const complex& y)
{
    return x == real(y) && imag(y) == 0;
}
```

这里操作符+的重载是定义在非成员函数中的，对应下面三种用法
```c++
{
    complex c1(2, 1);
    complex c2;
    c2 = c1 + c2;
    c2 = c1 + 5;
    c2 = 7 + c1;
}
```

加法返回的一定是值，不是引用

## 临时对象
```c++
inline complex operator + (double x, const complex& y)
{
    return complex(x, + real(y), imag(y));
}
```
这里面，complex(x, + real(y), imag(y));
typename();的形式，是临时对象

<< 运算符重载不能写为成员函数，成员函数必须作用在所属的类(左值)上
<<的用法：
```c++
cout << complex(2,1);
```
```c++
#include <iostream.h>
ostream& operator << (ostream& os, const complex& x)
{
    return os << '(' << real(x) << ',' << imag(x) << ')';
}
```
ostream& os 这个参数就是 cout
ostream& os 不能加const，因为在流输出时会改变cout
返回类型不能为void，因为需要支持连续<<

## 带有指针数据的类
### 框架
```c++
string.h

#ifndef __MYSTRING__
#define __MYSTRING__

class string
{
    ...
};

String::function(...)...
Global_function(...)...

#endif

string-test.cpp

int main()
{
    // 对应几个构造函数
    String s1();
    String s2("hello");
    // 拷贝构造
    String s3(s1);
    cout << s3 << endl;
    // 拷贝赋值，需要操作符重载
    s3 = s2;

    cout << s3 << endl;
}
```

### 构造函数
拷贝构造和拷贝赋值的操作符重载，编译器会自动给class默认建立，是简单的一个字节一个字节的拷贝

但是编译器带的拷贝构造和拷贝赋值不一定能够满足需求，比如对于带指针的String类，拷贝赋值是让两个变量指向同一个字符串

带有指针成员的类，必须有拷贝构造和拷贝赋值！！！

```c++
class String
{
public:
    String(const char* cstr=0);
    // 拷贝构造
    String(const String& str);
    // 拷贝赋值的操作符重载
    String& operator = (const String& str);
    // 析构函数
    // 类的实体“死亡”的时候，调用析构函数
    ~String();
    // 对于上面的complex类，数据相当于在complex这个类中的，创建一个类，就会有一组数据，String中会动态地申请内存，“数据”只是一个指针，所以需要析构

    char* get_c_str() const {return m_data;}

private:
    char* m_data;

};

inline String::String(const char* cstr=0)
{
    if(cstr)
    {
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data, cstr);
    }
    else
    {
        m_data = new char[1];
        *m_data = '\0';
    }
}

inline String::~String()
{
    delete[] m_data;
}
```

用法
```c++
{
    String s1();
    String s2("hello");

    String* p = new String("hello");
    delete p;
}
```

### 拷贝构造
使用默认的拷贝构造，比如
```c++
String a("Hello");
String b("World");
b = a;
```
这样会使b的m_data与a的m_data指向同一个字符串，b的m_data指向的“World”内存泄露

```c++
inline String::String(const String& str)
{
    m_data = new char[strlen(str) + 1];
    strcpy(m_data, str.m_data);
}

{
    String s1("hello");
    // 这两句意思完全相同，一个用拷贝构造，一个用拷贝赋值操作符重载
    String s2(s1);
    String s2 = s1;
}
```
### 拷贝赋值

```c++
inline String::String& operator = (const String& str)
{
    // 自我赋值检测
    // 这里自我赋值检测必须写，如果不写，直接delete，就把自己delete掉了
    if(this == str)
    {
        return *this;
    }

    delete[] m_data;
    m_data = new char[strlen(str) + 1];
    strcpy(m_data, str);
    return m_data;
}
```
output函数重载
```c++
#include <iostream.h>

ostream& operator << (ostream& os, const String& str)
{
    os << str.get_c_str();
    return os;
}
```
```c++
class Complex{...};
// stack object
// 生命期在函数作用域范围
// 在作用域结束时自动清理

int function()
{
    Complex c1(1, 2);
}

// static local object
// 在函数作用域中定义
// 生命期在作用域外仍然存在，直到程序结束
int function()
{
    static Complex c1(1, 2);
}

// global object
// 在全局作用域（函数外）定义
// 生命期在整个程序期间
Complex c1(1, 2);
int main()
{

}

// heap object
int function()
{
    Complex* p = new Complex;
    ...
    // delete时调用Complex类的析构函数
    // Complex类没有自己写析构函数，编译器有默认的析构函数
    // 离开函数作用域后,指针p消亡,但是p指向的内存区域没有被释放
    delete p;
}

int function()
{
    Complex* p = new Complex;
    ...
    // 这里没有delete,function函数执行完毕后,就没有机会再释放内存,造成内存泄漏
}
```
```c++
Complex* p = new Complex(1,2);
```
上面操作操作被编译器转化为:
```c++
Complex* p;
// operator new是C++提供的函数
// 内部调用malloc
void* mem = operator new(sizeof(Complex));
// 强制类型转换
p = static_cast<Complex*>(mem);
// 调用Complex类的构造函数
pc->Complex::Complex(1, 2);
```
delete pc;
编译器将上面操作转化为:
```c++
// 调用析构函数
Complex::~Complex(pc);
// 调用operator delete,释放内存
operator delete(pc);
```
对于String类
```c++
String* ps = new String("Hello");
delete ps;

// ps操作转化为:
// 调用String类的析构函数,将m_data指针指向的字符串的内存空间释放
String::~String(ps);
// 内部调用free(ps),将ps本身释放
operator delete(ps);
```

array new, array delete
```c++
String* p = new Stirng[3];
...
// 这里new []需要搭配delete[],会调用三次dtor函数
delete[] p;
// 如果这样,只会调用1次dtor,保存String指针的内存空间被释放了,String指针指向的字符串在dtor析构函数中释放,这里只调用了1次,造成内存泄漏
delete p;
```

static
首先看
```c++
class Complex{
public:
    double real() const {return re;}

private:
    double re, im;
};

Complex c1, c2, c3;
cout << c1.real();
cout << c2.real();

// 为什么可以用c1.real()取出实部呢?
// 实际上, 函数是:
cout << Complex::real(&c1);

// 对于同一个类的不同实例化对象,non-static的数据可能有多个,但是non-static的函数在代码中只有1份,通过this pointer来实现不同实例化对象的调用

// 实际上,编译器会在 non-static member 前面加上 this->
// 但是函数参数中一定不能加this!!!
double real() const {return this->re;}

// static 成员数据在代码中只有1份,不管有多少个实例化的对象,适合用来保存多个对象共有的数据

// static成员函数在代码中也只有1份,没有this pointer,所以不能访问non-static data member,只能访问static data member
```

```c++
class Account{
public:
    static double m_rate;
    static void set_rate(const double& x) {m_rate = x;}
}
//static member data 要在类的声明外面初始化,像全局变量一样
double Account::m_rate = 8.0;
int main(){
    // non-static member function因为和某一个实例化的对象无关,可以通过class name调用

    Account::set_rate(5.0);

    Account a;
    // 也可以通过实例化的对象调用
    a.set_rate(7.0);
}
```

singleton设计模式
如果希望类只产生1个对象,可以使用singleton设计模式,在private区实现构造函数
```c++
class A{
public:
    // static member function,只能访问static 数据
    // 外界不能创建A的实例化对象,但是通过这个static函数可以取得A自带的实例化对象a
    static A& getInstance{return a;}
    setup() {...}

private:
    // 构造函数放在private,不希望外界创建A的实例化对象
    A();
    A(const A& rhs);
    // A这个类中自带一个static member data,而且是A,也就是说,只要有A这个类的声明,程序中就会有一个A类的实例化对象a
    static A a;
}

int main(){
    // 这样来调用A类的自带实例化对象的setup函数
    A::getInstance().setup();
}

```

这样不管有没有实例化,都存在一个A自带的实例化对象a,造成资源浪费
下面这样更好,Meyers Singleton
```c++
class A{
public:
    static A& getInstance();
    setup() {...}

private:
    A();
    A(const A& rhs);
}

A& A::getInstance()
{
    // getInstance时才创建实例化对象
    // 因为外部想要使用A,一定要通过getInstance()获取实例化对象
    static A a;
    return a;
}

int main(){
    A::getInstance().setup();
}
```

类模板

在创建类的实例化对象时再决定类型

模板是类型
```c++
template<typename T>
class complex
{
public:
    complex(double r = 0, double i = 0)
        : re (r), im (i)
    {}
    complex& operator += (const complex&);
    double real () const {return re;}
    double image () const {return im;}
private:
    T re, im;
    friend complex& __doapl (complex*, const complex&);
};

{
    complex<double> c1(2.5, 1.5);
    complex<int> c2(2, 6);
}
```

模板是类

```c++
class Stone{
public:
    stone(int w, int h, int we)
    : _w(w), _h(h), _weight(we)
    { }

    bool operator < (const Stone& rhs) const { return _weight < rhs.weight}
private:
    int _w, _h, _weight;
}

int main(){
    Stone r1(2, 3), r2(3, 3), r3;
    // 这里和类的模板的使用不同,不必用<>指定类型,编译器会进行参数推导
    r3 = min(r1, r2);
}
```

由于min操作都是类似与 b < a ? b : a 的操作,因此可以将输入给min的参数设计成类的模板

```c++
template<class T>
inline T& min(const T& a, const  T& b){
    return b < a ? b : a;
}
```
这里最后的<操作调用的是Stone::operator <

namespace
```c++
namespace std
{
    ...
}

// 两种使用namespace的方式
// directive
using namespace std;
// declaration
using namespace std::out;
// 
``` 