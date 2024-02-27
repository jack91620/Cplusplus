#cpp

# 类的声明

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

