1. 分开进行编译(先进行词法分析，再进行语法分析)：可以让变量以及类的定义按照任意次序拜访

2. Array不能回收

3. String不能被创建，只能通过ReadLine等获得，只支持读取、比较、打印

   比较是判断字符串内容是否相等

4. Function

   * **没有检查返回值是否合法**
   * **没有虚函数**
   * **没有函数重载**

5. 函数调用Function Invocation

   * 函数调用的参数表达式的计算是从左往右(C/C++中没有指定)

6. Class类

   * 所有的成员变量都是protected的，即只能被本类和子类访问
   * 所有的成员函数、方法都是public类型，可以全局访问，所以只能通过方法访问对象属性
   * **所有的类的定义都是全局的，类不能在函数内定义**
   * 在类中this的使用是可选择的。

7. Objects对象

   * 所有的对象都是动态在堆上使用new运算符分配的
   * new分配的对象必须是一个class名

8. Inheritance继承

   * Decaf支持单继承，并且支持重写(返回值和参数均一致)
   * 支持动态调用，在编译期间不用指定重写函数的具体调用函数，而是在运行的时候动态绑定
   * 子类不能重写继承得到的变量
   * No overloading
   * 父类对象可以引用子类对象实例，Animal animal = new Cow;
   * **没有向下类型转换**
   * 对象数组是没有继承关系的

9. Type Equivalence and Compatibility

   * 类型相当是单向的，父类和子类是类型相当的
   * 类型相容是双向的，必须双方在任何情况下可以互换
   * null与所有自定义类型是相容的

10. Assignment赋值

    * 对于基本数据类型是值拷贝
    * 对于对象数据类型是浅拷贝即引用拷贝
    * 赋值时等号右边的表达式的类型必须相容于等式左边的类型

11. Control structures控制语句

    * else与最近的if匹配
    * if,while,for语句中的测试语句必须有bool类型(C/C++中for没有)
    * break只能出现在while和for循环中
    * return返回值必须与函数返回值相容

12. 表达式

    * 在表达式中不支持类型转换

    * 操作符优先级：

      * [ . (array indexing and field selection)
      * ! - (unary minus, logical not)
      * \* / % (multiply, divide, mod)
      * \+ \- (addition, subtraction)
      * < <= > >= (relational)
      * == != (equality)
      * && (logical and)
      * || (logical or)
      * = (assignment)

13. Library Functions 库函数
    * Decaf 有很小的一个标准库用于允许简单的I/O以及内存分配，分别是Print, ReadInteger, ReadLine, and NewArray.
    * Print的参数可以是string, int, bool
    * NewArray的返回值是T类型的一个数组
    * ReadLine读取用户输入的一串字符
    * ReadInteger读取用户输入的一行文本，用atoi将其转换成整型，如果输入了不合法的数组，返回0
14. Decaf linking
    * Decaf不支持分离的模块或者声明和定义分开
    * 只用检查是否有一个全局函数main
15. Runtime Checks运行时检查
    * 数组越界
    * 传递给NewArray的大小必须是一个正数
    * 当运行错误产生时，需要有合适的信息输出到终端中
16. What Decaf Is Not
    * Decaf没有为没有初始化的变量赋初值
    * Decaf没有检查没有初始化的变量
    * Decaf没有检查函数是否根据定义返回了一个对应的变量
    * Decaf没有检查数组和对象在使用前是否已经分配了空间
    * Decaf没有检查永远不能到达的代码
    * Decaf没有回收函数或者垃圾回收机制，一旦被分配就不会再回收
    * Decaf不支持构造函数和析构函数