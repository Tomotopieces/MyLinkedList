#pragma once

template<typename T>
class MyList {      //链表
private:
    struct MyData {                     //用于存放数据的结构体
        T data = 0;                     //数据
        MyData* next = nullptr;         //存放后一个数据的地址
        MyData* previous = nullptr;     //存放前一个数据的地址，因为有这一项，所以这是一个双向链表（双链表），只有next的叫单链表（链表）
    };

    MyData* _begin = nullptr;           //链表头，不存放数据
    MyData* _end = nullptr;             //链表尾，不存放数据
    int _length = 0;                    //链表长度

    const bool _IndexCheck(int index)const;     //数组越界检测

    explicit MyList(MyList<T>&& list);          //禁止移动构造
public:
    //Constructors

    MyList();                                   //无参构造
    MyList(const T data);                       //构造时自带一个数据，数据内容为data
    MyList(const T data, const int length);     //构造时自带length个数据，每个数据内容都为data
    MyList(const T* list, const int length);    //通过一个已经存在的普通数组来构造
    MyList(const MyList<T>& list);              //复制构造，复制另一个链表

    //Destructor

    ~MyList<T>();           //析构函数，不需要手动调用，链表生命周期结束时程序会自动调用

    //Operators

    MyList<T>& operator=(const MyList<T>& list);            //运算符重载     list1 = list2;      list1复制list2的内容，list1的原内容被删除
    MyList<T> operator+(const MyList<T>& list);             //运算符重载     list1 + list2;      返回两个链表相加的结果
    MyList<T>& operator+=(const MyList<T>& list);           //运算符重载     list1 += list2;     将list2的数据添加到list1的结尾
    T& operator[](const int index)const;                    //运算符重载     list[i];            如同数组一般获得数据或者设置数据
    const bool operator==(const MyList<T>& list)const;      //运算符重载     list1 == list2;     比较两个链表的数据是否完全一致
    

    //Gets

    const T GetIndex(const int index)const;                 //通过位置获得数据
    const int GetLength()const;                             //获得链表长度

    //Sets

    MyList<T>& Set(const int index, const T data);          //通过位置设置数据

    //List Operations

    MyList<T>& PushBack(T data);                            //向链表尾增加数据，通过位置插入时无法插入到此位置
    MyList<T>& PopBack();                                   //将链表尾数据删除，通过位置删除时无法删除到此位置
    MyList<T>& Insert(const int index, const T data);       //向位置前插入数据
    MyList<T>& Remove(const int index);                     //将位置上的数据删除
    MyList<T>& Add(const MyList<T>& list);                  //将新链表数据添加到这个链表的结尾
    MyList<T>& Add(const T* list, const int length);        //将数组数据添加到这个链表的结尾
    MyList<T>& Clear();                                     //清空链表
    MyList<T>& Sort();                                      //按从小到大来排列链表
    int Find(const T data)const;                            //在链表中寻找数据，返回数据的位置，未找到则返回-1
};

template<typename T>
const bool MyList<T>::_IndexCheck(int index) const
{
    if (index >= this->_length || index < 0) {
        std::cerr << "Index out of bounds.";
        system("pause");
        exit(-1);       //退出程序
    }
    else {
        return true;
    }
}

template<typename T>
MyList<T>::MyList()
{
    //先分配空间
    this->_begin = new MyData;
    this->_end = new MyData;
    //然后首尾相连
    this->_begin->next = this->_end;
    this->_end->previous = this->_begin;
    this->_length = 0;
}

template<typename T>
MyList<T>::MyList(const T data)
{
    this->_begin = new MyData;
    this->_end = new MyData;
    this->_begin->next = this->_end;
    this->_end->previous = this->_begin;

    //创建新数据
    MyData* newData = new MyData;
    newData->data = data;

    //将数据与首尾相连
    newData->next = this->_end;
    newData->previous = this->_begin;
    this->_begin->next = newData;
    this->_end->previous = newData;
    this->_length = 1;
}

template<typename T>
MyList<T>::MyList(const T data, const int length)
{
    this->_begin = new MyData;
    this->_end = new MyData;
    this->_begin->next = this->_end;
    this->_end->previous = this->_begin;

    //循环创建新的数据，然后前后相连
    for (int i = 0; i < this->_length; ++i) {
        MyData* newData = new MyData;
        newData->data = data;
                                                    //添加数据到尾部时，数据连接的逻辑顺序
        newData->next = this->_end;                 //将 新数据 的 next 连向 end
        newData->previous = this->_end->previous;   //将 新数据 的 previous 连向 旧的最后一项
        this->_end->previous->next = newData;       //将 旧的最后一项 的 next 连向新数据
        this->_end->previous = newData;             //将 end 的 previous 连向新数据
        this->_length++;                            //改变长度值
    }
}

template<typename T>
MyList<T>::MyList(const T* list, const int length)
{
    this->_begin = new MyData;
    this->_end = new MyData;
    this->_begin->next = this->_end;
    this->_end->previous = this->_begin;

    this->_length = length;
    for (int i = 0; i < this->_length; ++i) {
        MyData* newData = new MyData;
        newData->data = list[i];
        newData->next = this->_end;
        newData->previous = this->_end->previous;
        this->_end->previous->next = newData;
        this->_end->previous = newData;
    }
}

template<typename T>
MyList<T>::MyList(const MyList<T>& list)
{
    this->Add(list);
}

template<typename T>
MyList<T>::~MyList()
{
    Clear();
}

template<typename T>
MyList<T>& MyList<T>::operator=(const MyList<T>& list)
{
    this->Clear().Add(list);
    return this->Clear().Add(list);
}

template<typename T>
MyList<T> MyList<T>::operator+(const MyList<T>& list)
{
    MyList newList = *this;
    return newList.Add(list);       //这里返回的不是对象本身，只是一个临时的结果
}

template<typename T>
inline MyList<T>& MyList<T>::operator+=(const MyList<T>& list)
{
    return this->Add(list);
}

template<typename T>
T& MyList<T>::operator[](const int index) const
{
    this->_IndexCheck(index);               //有关于index的操作都需要先检查一次是否发生了数组越界
    MyData* location = this->_begin->next;
    for (int i = 0; i < index; ++i) {
        location = location->next;
    }
    return location->data;
}

template<typename T>
const bool MyList<T>::operator==(const MyList<T>& list) const
{
    if (this == &list) {                            //如果对象与对比的新数组地址相同，则表示同一个数组，无需比较
        return true;
    }
    if (this->_length != list._length) {            //长度不同，无需继续比较
        return false;
    }
    for (int i = 0; i < this->_length; ++i) {       //数据挨个比较
        if (this->GetIndex(i) != list.GetIndex(i)) {
            return false;
        }
    }
    return true;
}

template<typename T>
const T MyList<T>::GetIndex(const int index) const
{
    return this->operator[](index);     //直接调用[]方法，但是GetIndex后的数据是原数据的拷贝，不影响原数据
}

template<typename T>
const int MyList<T>::GetLength() const
{
    return this->_length;
}

template<typename T>
MyList<T>& MyList<T>::Set(const int index, const T data)
{
    this->operator[](index) = data;     //直接调用[]方法来设置数据，相当于     list[index] = data;
    return*this;
}

template<typename T>
MyList<T>& MyList<T>::PushBack(T data)
{
    MyData* newData = new MyData;
    newData->data = data;

    newData->previous = this->_end->previous;
    newData->next = this->_end;
    this->_end->previous->next = newData;
    this->_end->previous = newData;
    this->_length++;
    return*this;
}

template<typename T>
MyList<T>& MyList<T>::PopBack()
{                                                       //从尾部删除数据时，数据连接的逻辑顺序
    MyData* deleteData = this->_end->previous;          //将 删除的数据 的地址保存
    deleteData->previous->next = this->_end;            //将 旧的倒数第二个数据 的 next 连向 end
    this->_end->previous = deleteData->previous;        //将 end 的 previous 连向 旧的倒数第二个数据
    delete deleteData;                                  //删除 删除的数据
    this->_length--;                                    //改变长度值
    return*this;
}

template<typename T>
MyList<T>& MyList<T>::Insert(const int index, const T data)
{
    this->_IndexCheck(index);
    MyData* newData = new MyData;
    newData->data = data;
    MyData* location = this->_begin->next;              //location时用于定位的指针，开始时位于0号数据位置
    for (int i = 0; i < index; ++i) {                   //循环前进index次来定位
        location = location->next;
    }
                                                        //向中间插入数据时，数据连接的逻辑顺序
    newData->next = location;                           //新数据 的 next 连向 定位数据
    newData->previous = location->previous;             //新数据 的 previous 连向 定位数据的前一项数据
    location->previous->next = newData;                 //定位数据的前一项数据 的 next 连向 新数据
    location->previous = newData;                       //定位数据 的 previous 连向 新数据
    this->_length++;                                    //改变长度值
    return*this;
}

template<typename T>
MyList<T>& MyList<T>::Remove(const int index)
{
    this->_IndexCheck(index);
    MyData* location = this->_begin->next;              //定位数据就是要删除的数据
    for (int i = 0; i < index; ++i) {
        location = location->next;
    }
                                                        //从中间删除数据时，数据连接的逻辑顺序
    location->previous->next = location->next;          //定位数据的前一项数据 的 next 连向 定位数据的后一项数据
    location->next->previous = location->previous;      //定位数据的后一项数据 的 previous 连向 定位数据的前一项数据
    delete location;                                    //删除 定位数据
    this->_length--;                                    //改变长度值
    return*this;
}

template<typename T>
MyList<T>& MyList<T>::Add(const MyList<T>& list)
{
    if (list._length <= 0) {
        return*this;
    }
    for (int i = 0; i < list._length; ++i) {
        MyData* newData = new MyData;
        
        newData->data = list.GetIndex(i);               //向链表尾部添加新数据
        newData->next = this->_end;
        newData->previous = this->_end->previous;
        this->_end->previous->next = newData;
        this->_end->previous = newData;
    }
    this->_length += list._length;
    return*this;
}

template<typename T>
MyList<T>& MyList<T>::Add(const T* list, const int length)
{
    return this->Add(MyList(list, length));             //将数组转化为链表，然后引用上一个方法
}

template<typename T>
MyList<T>& MyList<T>::Clear()
{
    if (this->_length == 0) {
        return*this;
    }
                                                        //清空链表的逻辑顺序
    MyData* location;                                   //定位数据
    for (location = this->_begin->next->next;           //从第二项数据开始
        location != this->_end;                         //location到前进到end时退出
        location = location->next) {                    //location向后前进一项
        delete location->previous;                      //删除location的前一项
    }
    delete location->previous;                          //删除location的前一项，此时location为end
    this->_begin->next = this->_end;                    //首尾相连
    this->_end->previous = this->_begin;
    this->_length = 0;                                  //改变长度值
    return*this;
}

template<typename T>
MyList<T>& MyList<T>::Sort() {

}

//快速排序
MyList<int>& MyList<int>::Sort()
{
    if (this->_length <= 1) {
        return*this;
    }
    MyList<int> left, right;
    MyData* firstData = this->_begin->next;
    MyData* location = firstData->next;
    for (int i = 1; i < this->_length; ++i) {
        if (location->data < firstData->data) {
            left.PushBack(location->data);
        }
        else {
            right.PushBack(location->data);
        }
        location = location->next;
    }
    left.Sort();
    right.Sort();
    this->operator=(left.PushBack(firstData->data).Add(right));

    return*this;
}

//同上
MyList<double>& MyList<double>::Sort()
{
    if (this->_length <= 1) {
        return*this;
    }
    MyList<double> left, right;
    MyData* firstData = this->_begin->next;
    MyData* location = firstData->next;
    for (int i = 1; i < this->_length; ++i) {
        if (location->data < firstData->data) {
            left.PushBack(location->data);
        }
        else {
            right.PushBack(location->data);
        }
        location = location->next;
    }
    left.Sort();
    right.Sort();
    this->operator=(left.PushBack(firstData->data).Add(right));

    return*this;
}

template<typename T>
int MyList<T>::Find(const T data) const
{
    for (int i = 0; i < this->_length; ++i) {
        if (this->operator[](i) == data) {      //遍历循环
            return i;
        }
    }
    return -1;
}
