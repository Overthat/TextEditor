#ifndef SL
#define SL

#include <iostream>
#include <fstream>
#include "String.cpp"
using namespace std;

#ifndef MAXSIZE
#define MAXSIZE 80
#endif

// 节点类
template <typename T>
class Node
{
public:
    Node()  = default;
    Node(int num): _num(num){}
    Node(T value, Node* next, int num):
         _value(value), _next(next),  _num(num){}
public:
    // 每个节点的序号
    int _num; 
    T _value;
    Node* _next;
};


//单链表类
template <typename T>
class SingleLink
{
private:
    // 总节点数
    int count;
    // 指向头节点的指针
    Node<T>* phead; 
public:
    typedef Node<T>* pointer;
    SingleLink();
    ~SingleLink();

    int size(){return count;}
    bool isEmpty(){return count == 0;}

    pointer insert(int index, T t);
    pointer insert_head(T t);
    pointer insert_last(T t);

    pointer del(int index);
    pointer delete_head(); 
    pointer delete_last(); 

    pointer getHead(){return phead->_next;} 

    void mInsert(char* s, int len, int row, int col);
    void mDelete(int row, int col, int  len);
    void mReplace(char* s, int slen, int row, int col, int len);
    void mSearch(char* s);

    void show();
    void mSave();
    
private:
    pointer getNode(int index);
    pointer getNode2(int index);
    pointer insert2(int index, T t);
    void update_num(pointer p);
    void update_num2(pointer p);
    void update_rest(pointer p);

};


template <typename T>
SingleLink<T>::SingleLink(): count(0), phead(nullptr)
{
    phead = new Node<T>(0);
    phead->_next = nullptr;
}


template <typename T>
SingleLink<T>::~SingleLink()
{
    while(count != 0)
    {
        delete_last();
    }

    delete phead;
}


// 通过num遍历，返回第index行的节点指针
template <typename T>
Node<T>* SingleLink<T>::getNode(int index)
{
    if (index > count || index < 0)
    {
        return nullptr;
    }

    pointer p = phead;

    while(p->_num != index)
        p = p->_next;

    return p;
}


// 指定节点的后面插入节点
template <typename T>
Node<T>* SingleLink<T>::insert(int index, T t)
{
    pointer prenode = getNode(index);

    if (prenode)
    {
        pointer newNode = new Node<T>(t, prenode->_next, count+1);
        prenode->_next = newNode;
        count++;
        return newNode;
    }

    return nullptr;
}

// 头插法
template <typename T>
Node<T>* SingleLink<T>::insert_head(T t)
{
    return insert(0, t);
}

// 尾插法
template <typename T>
Node<T>* SingleLink<T>::insert_last(T t)
{
    return insert(count, t);
}



// 删除指定位置的节点
template <typename T>
Node<T>* SingleLink<T>::del(int index)
{
    if (isEmpty())
        return nullptr;

    pointer ptrNode = getNode(index - 1);
    pointer delNode = ptrNode->_next;
    ptrNode->_next = delNode->_next;
    count--;
    delete delNode;
    return ptrNode->_next;
}


// 从第一个节点开始删除节点
template<typename T>
Node<T>* SingleLink<T>::delete_head()
{
    return del(0);
}


// 从最后一个节点开始删除节点
template<typename T>
Node<T>*SingleLink<T>::delete_last()
{
    return del(count);
}


// 指定节点后面的节点num加一
template <typename T>
void SingleLink<T>::update_num(pointer p)
{
    do
    {
        p->_num++;
        p = p->_next;
    } while(p != nullptr);
}


// 指定节点后面的节点num减一
template <typename T>
void SingleLink<T>::update_num2(pointer p)
{
    do
    {
        p->_num--;
        p = p->_next;
    } while(p != nullptr);
}


// 超出MAXSIZE新开一行的插入函数
// index为行数， t为数据
template <typename T>
Node<T>* SingleLink<T>::insert2(int index, T t)
{
    pointer prenode = getNode(index);

    if (prenode)
    {
        pointer newNode = new Node<T>(t, prenode->_next, prenode->_next->_num);
        prenode->_next = newNode;
        //更新后续节点的num
        update_num(newNode->_next);
        count++;
        return newNode;
    }

    return nullptr;
}


// 插入函数
// s = 需要插入的字符串 len = 字符串长度 row = 指定第几行 col = 指定第几个字符前插入，索引从0开始
template <typename T>
void SingleLink<T>::mInsert(char* s, int len, int row, int col)
{
    if (row < 1 || row > count)
    {
        cout << "插入失败，请重新输入行数" << endl;
        return;
    }

    pointer p = getNode(row);
    // 插入后超出MAXSIZE，把s拆成两部分
    if (p->_value.get_len() + len > MAXSIZE)
    {
        // A_num为s前半部分长度
        int B_num = p->_value.get_len() + len - MAXSIZE;
        int A_num = len - B_num;
        // 申请空间储存前后两段数据
        char* Ac = new char[A_num+1];
        char* Bc = new char[B_num+1];

        int i = 0;
        for (; i < A_num; i++)
            Ac[i] = s[i];
        Ac[i] = '\0';

        int j = 0;
        for (; j < B_num; j++, i++)
            Bc[j] = s[i];
        Bc[j] = '\0';
        // 转化为串类型
        SString A(Ac), B(Bc);
        // 前半段A直接插入
        p->_value.StrInsert(col, A);
        // 后半段B调用insert2函数增加一个节点再插入
        insert2(row, B);
        // 别忘了释放new创建的空间
        delete Ac, Bc;
    }
    // 长度没有超过MAXSIZE,直接插入
    else
    {
        SString ss(s);
        p->_value.StrInsert(col, ss);
    }
}


// 删除字符串函数
// row = 行数 col = 列数 len = 需要删除的字符串长度
// (无检查输入合法功能)
template <typename T>
void SingleLink<T>::mDelete(int row, int col, int len)
{
    pointer p = getNode(row);
    p->_value.StrDelete(col, len);
    // 检查并更新
    update_rest(p);
}


// 若删除后此行无数据,则删除此节点并更新后续num值
template <typename T>
void SingleLink<T>::update_rest(pointer p)
{
    if (p->_value.get_len() == 0)
    {
        // 更新后续num值
        update_num2(p->_next);
        del(p->_num);
    }
}


// 替换字符串函数
// s = 将要替换的字符串 slen = 其长度 row = 行数 len = 列数 len = 替换多少个字符
template <typename T>
void SingleLink<T>::mReplace(char* s, int slen, int row, int col, int len)
{
    pointer p = getNode(row);
    p->_value.StrDelete(col, len);
    mInsert(s, slen, row, col);
}


// 查找函数
// s = 要查找的字符串
template <typename T>
void SingleLink<T>::mSearch(char* s)
{
    int index = 0;
    SString str(s);

    for (int i = 1; i <= count; i++)
    {
        pointer p = getNode(i);
        while (1)
        {
            index = p->_value.StrIndex(index, str);
            if (index == -1)
                break;
            if (index > 0)
            {
                cout << "要查找的字符串在第" << i << "行,第" << index << "列" << endl;
            }
            index++;
        }
    }
}


// 打印各行数据于屏幕上
template <typename T>
void SingleLink<T>::show()
{
    for (int i = 1; i <= count; i++)
    {
        pointer p = getNode(i);
        cout << p->_value.get_ch() << endl;
    }
}


// 保存数据到文件hi.txt
template <typename T>
void SingleLink<T>::mSave()
{
    ofstream f("hi.txt");
    for (int i = 1; i <= count; i++)
    {
        pointer p = getNode(i);
        f << p->_value.get_ch() << '\n';
    }

    f.close();

}


#endif