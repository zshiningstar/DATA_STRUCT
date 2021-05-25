#ifndef _STACK_STAR_H
#define _STACK_STAR_H

//栈先进后出
template <typename Type>
class Stack
{
private:
    enum {SIZE = 10};       //枚举量
    int stacksize;          //栈大小
    Type *items;            //栈中元素
    int top;                //栈顶部索引
public:
    explicit Stack(int ss = SIZE);      //指定这个构造器只能被明确的调用/使用，不能作为类型转换操作符被隐含的使用
    Stack(const Stack& st);             //复制构造函数
    virtual ~Stack() { delete [] items; }
     /*****************************************
     *******一个容器应具备的基本条件：*********
     *****************************************/
    bool isempty() { return top == 0; }         //判断栈是否为空
    bool isfull() { return top == stacksize; }  //判断栈是否装满
    bool push(const Type& item);                //添加元素
    bool pop(Type& item);                       //删除并返回栈顶部元素
    Type pop();     //弹出并返回顶部元素
    int size() { return top+1; }
    Stack & operator=(const Stack& st);         //重载=运算符
};

template <typename Type>
Stack<Type>::Stack(int ss) : stacksize(ss),top(0)
{
    items = new Type [stacksize];
}

template <typename Type>
Stack<Type>::Stack(const Stack& st)
{
    stacksize = st.stacksize;
    top = st.top;
    items = new Type [stacksize];
    for(int i=0;i<top;i++)
        items[i] = st.items[i];
}

template <typename Type>
bool Stack<Type>::push(const Type& item)
{
    if(top < stacksize)             //先判断是否装满
    {
        items[top++] = item;
        return true;
    }
    else
    {
        return false;
    }
}

template <typename Type>
bool Stack<Type>::pop(Type& item)
{
    if(top > 0)                     //先判断是否为空
    {
        item = items[top--];
        return true;
    }
    else
    {
        return false;
    }
}

template <typename Type>
Stack<Type>& Stack<Type>::operator=(const Stack& st)
{
    if(this == &st)
        return *this;
    delete [] items;
    stacksize = st.stacksize;
    top = st.top;
    items = new Type [stacksize];
    for(int i=0;i<top;i++)
        items[i] = st.items[i];
    return *this;
}

template <typename Type>
Type Stack<Type>::pop()
{
    if(top == 0)
        return 0;
    Type num = items[top--];
    return num;
}
#endif
