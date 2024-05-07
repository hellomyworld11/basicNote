### C

```c
1. ## 运算符
示例：#define EXAMPLE(n) x##n  ->   EXAMPLE(4)  x4
```



### C++对象模型

****

被弃用的特性
```C++
	

```





### C++知识点

#### 1.const

```
1. 修饰的变量不能再改变
2. 指向常量的指针(const char *p)  指针常量(char const *p)
3. 常量引用 
4. int getValue() const;  说明该函数不能修改成员变量
5. 修饰类成员变量 只能在初始化列表赋值 (引用类型的成员变量也需要初始化列表赋值)
延伸：
constexpr  常量表达式
```

#### 2.static

```
1.修饰局部变量，修改其存储区域和生存周期
2.修改全局函数，使其只能在此文件中使用
3.静态成员函数、成员变量 
```

#### 3.this

```
1.隐藏于非静态成员函数中 ，指向具体的对象
```

#### 4.用的少的关键字 & 描述符

```
1.
#pragma pack(n) 使用n字节对齐
2. 
decltype()  类型检查
```

#### 右值引用

```
绑定右值(临时对象，将要销毁的对象)的引用。一般表示对象的值
可以实现 传递语义和精确传递
作用 ：
消除两个对象交互时不必要的对象拷贝，节省运算存储资源，提高效率
```

#### 多态  虚函数 注意

```
编译时多态： 函数重载
运行时多态   虚函数：用 virtual 修饰成员函数，使其成为虚函数
！构造函数不能是虚函数 此时还没有虚指针
！虚析构函数
	基类的指针指向派生类对象时，delete时 能调用子类对象析构函数 防止内存泄漏
```

#### 内存管理

```
如何定义一个只能在堆上（栈上）生成对象的类？
堆上： 析构函数私有
栈上： 重载私有化new 和delete
```

#### ！智能指针

```
 #include <memory>

1.shared_ptr  共享对象  计数
2 unique_ptr  独占式
3 weak_ptr   共享但不拥有
4.auto_ptr 弃用
```

#### 强制类型转换

```
![20140713220242000](20140713220242000.jpg)![20140713220242000](20140713220242000.jpg)1.static_cast
	非多态类型的转换   子类向上转换(隐式) 安全  父类向下转换不安全
2.dynamic_cast
	多态类型的转换   类型检查
3.const_cast
	用于删除 const、volatile特性
4.reinterpret_cast
用于位的解释

```

####  实现通过类名new对象 （反射）

```
一般不同类型的对象 需要用很多if else 来 判断,导致每次有新类型都要该这部分代码。
解决方法:
	用 类名 和 构造类的函数 的映射关系，来替换if else ，每次只需要注册类，new 对象的时候传入类名即可。
	
	参考：https://www.cnblogs.com/onStateChange/p/6590543.html
	https://blog.csdn.net/xiaoqiang321/article/details/128698461
```



ObjectFactory.h

```
#ifndef __OBJECTFACTORY_H__
#define __OBJECTFACTORY_H__
 
#include <map>
#include <string>
#include <functional>
 
 //Object为基类， 不同子类继承于基类。
class Object
{
public:
    virtual std::string GetClassName() const = 0;
};
 
class ObjectFactory
{
public:
    static ObjectFactory& GetInstance();
 
    using ObjCreator = std::function<Object*(void)>;
    int RegisterObj(const std::string& className, ObjCreator objCreator);
 
    Object* CreateObj(const std::string& className);
 
private:
    ObjectFactory();
    ~ObjectFactory();
    ObjectFactory(const ObjectFactory&) = delete;
 
    std::map<std::string, ObjCreator> creatorMap_;
};

#define REGISTERCLASS(className) \
class className##Helper { \
public: \
    className##Helper() \
    { \
        ObjectFactory::GetInstance()->RegisterObject(#className, []() \
        { \
            auto* obj = new className(); \
            return obj; \
        }); \
    } \
}; \
className##PanelHelper g_##className##_panelhelper;// 初始化一个helper的全局变量，执行构造函数中的RegisterObject执行。


#endif
```

ObjectFactory.cpp

```
#include "ObjectFactory.h"
using namespace std;
 
ObjectFactory& ObjectFactory::GetInstance()
{
    static ObjectFactory instance_;
    return instance_;
}
 
int ObjectFactory::RegisterObj(const std::string& className, ObjCreator objCreator)
{
    creatorMap_.insert(make_pair(className, objCreator));
    return 0;
}
 
Object* ObjectFactory::CreateObj(const std::string& className)
{
    auto it = creatorMap_.find(className);
    if(it == creatorMap_.end())
    {
        return nullptr;
    }
    return it->second();
}
 
ObjectFactory::ObjectFactory()
{
}
 
ObjectFactory::~ObjectFactory()
{
}
```

测试

```
 REGISTERPANELCLASS(XXX)  //XXX为类名
 auto pObj = (Object*)ObjectFactory::GetInstance()->CreateObject("XXX");
```









### Effective C++

+ 尽量以  const 、 enum 、 inline 替换 define



###　GoogleC++规范

![](C++.assets/20140713220242000.jpg)

### Modern CPP Programming

#### 一.类型系统

```
C++类型分为 基础类型和混合类型。
基础类型： 
 1. 浮点型 整型
 2. void
 3. nullptr_t
 混合类型:
 1.引用
 2.枚举
 3. class struct union
 ...
 图示如下
```

![image-20240409171857365](C++.assets/image-20240409171857365.png)

auto 关键字 可以被编译器翻译 

```
auto a = 1 + 2;  // auto 被推断为int
auto 可以代替复杂的类型声明。
for(auto x : arr)
	...
```

