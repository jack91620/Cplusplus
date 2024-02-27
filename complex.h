#ifndef COMPLEX_H
#define COMPLEX_H

class complex
{
public:
    // 外部可以看到的
    // 构造函数
    // 在创建类的实例时，自动调用的函数
    // “初始化”的函数
    // 构造函数的名称一定和类名相同
    // 两个0是默认的实参，如果创建实例时不传入实参，用这个默认实参
    // 所有的函数都可以有默认实参

    // 构造函数不需要有返回类型，返回值的类型就是这个类
    complex(double r = 0, double i = 0)
    // initialization list，初始列
    // 只有构造函数有这个语法
    // 将r给re, 将i给im
    // 这样写，在创建对象的时候将两个变量初始化
    // 如果在大括号里面赋值，就是在创建对象的时候进行的操作，不是初始化
    // 速度和效率的考虑
        : re (r), im (i)
    {}
    // 构造函数可以有很多个
    // 如果希望以多种不同的方式创建1个对象，就可以写多个构造函数
    // “重载”

    /*
    下面这个构造函数是非法的
    因为上面的构造函数有默认初始值
    如果存在这个构造函数，初始化时编译器不知道要调用哪个
    complex () : re(0), im(0) {}
    */

    /*
    外部可以这样用构造函数初始化对象
    complex c1;
    complex c2();
    */
    complex& operator += (const complex&);
    // real, image两个函数在类的声明中定义，是内联函数
    // “建议”编译器内联，
    // 最好都内联，但是最终看编译器的决定
    double real () const {return re;}
    double image () const {return im;}

private:
    // 私有的，外部不允许访问的
    double re, im;

    friend complex& __doapl (complex*, const&);
};

// real 函数在外部重载
// re没定义，需要全局定义么？
// 外部重载了，还算complex类的public函数么？
// 不能有const
void real(double r) { re = r; }
// 重载的两个函数在编译之后是不同的实体，不是同一个函数
#endif