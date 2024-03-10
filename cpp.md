# cpp

## 类的声明

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