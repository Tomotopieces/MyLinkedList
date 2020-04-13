#pragma once

template<typename T>
class MyList {
private:
    struct MyData {
        T data = 0;
        MyData* next = nullptr;
        MyData* previous = nullptr;
    };

    MyData* _begin = nullptr;
    MyData* _end = nullptr;
    int _length = 0;

    const bool _IndexCheck(int index)const;

    explicit MyList(MyList<T>&& list);
public:
    //Constructors

    MyList();
    MyList(const T data);
    MyList(const T data, const int length);
    MyList(const T* list, const int length);
    MyList(const MyList<T>& list);

    //Destructor

    ~MyList<T>();

    //Operators

    MyList<T>& operator=(const MyList<T>& list);
    MyList<T>& operator+(const MyList<T>& list);
    T& operator[](const int index)const;
    const bool operator==(const MyList<T>& list)const;
    

    //Gets

    const T GetIndex(const int index)const;
    const int GetLength()const;

    //Sets

    MyList<T>& Set(const int index, const T data);

    //List Operations

    MyList<T>& PushBack(T data);
    MyList<T>& PopBack();
    MyList<T>& Insert(const int index, const T data);
    MyList<T>& Remove(const int index);
    MyList<T>& Add(const MyList<T>& list);
    MyList<T>& Add(const T* list, const int length);
    MyList<T>& Clear();
    MyList<T>& Sort();
    int Find(const T data)const;
};

template<typename T>
const bool MyList<T>::_IndexCheck(int index) const
{
    if (index >= this->_length || index < 0) {
        std::cerr << "Index out of bounds.";
        system("pause");
        exit(-1);
    }
    else {
        return true;
    }
}

template<typename T>
MyList<T>::MyList()
    : _length(0)
{
    this->_begin = new MyData;
    this->_end = new MyData;
    this->_begin->next = this->_end;
    this->_end->previous = this->_begin;
}

template<typename T>
MyList<T>::MyList(const T data)
    : _length(1)
{
    this->_begin = new MyData;
    this->_end = new MyData;
    this->_begin->next = this->_end;
    this->_end->previous = this->_begin;

    MyData* newData = new MyData;
    newData->data = data;
    newData->next = this->_end;
    newData->previous = this->_begin;
    this->_begin->next = newData;
    this->_end->previous = newData;
}
template<typename T>
MyList<T>::MyList(const T data, const int length)
    : _length(length)
{
    this->_begin = new MyData;
    this->_end = new MyData;
    for (int i = 0; i < this->_length; ++i) {
        MyData* newData = new MyData;
        newData->data = data;
        newData->next = this->_end;
        newData->previous = this->_end->previous;
        this->_end->previous->next = newData;
        this->_end->previous = newData;
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
    this->Clear();
    this->Add(list);
    return*this;
}

template<typename T>
MyList<T>& MyList<T>::operator+(const MyList<T>& list)
{
    this->Add(list);
    return*this;
}

template<typename T>
T& MyList<T>::operator[](const int index) const
{
    this->_IndexCheck(index);
    MyData* location = this->_begin->next;
    for (int i = 0; i < index; ++i) {
        location = location->next;
    }
    return location->data;
}

template<typename T>
const bool MyList<T>::operator==(const MyList<T>& list) const
{
    if (this == &list) {
        return true;
    }
    if (this->_length != list._length) {
        return false;
    }
    for (int i = 0; i < this->_length; ++i) {
        if (this->GetIndex(i) != list.GetIndex(i)) {
            return false;
        }
    }
    return true;
}

template<typename T>
const T MyList<T>::GetIndex(const int index) const
{
    return this->operator[](index);
}

template<typename T>
const int MyList<T>::GetLength() const
{
    return this->_length;
}

template<typename T>
MyList<T>& MyList<T>::Set(const int index, const T data)
{
    this->operator[](index) = data;
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
{
    MyData* deleteData = this->_end->previous;
    deleteData->previous->next = this->_end;
    this->_end = deleteData->previous;
    delete deleteData;
    this->_length--;
    return*this;
}

template<typename T>
MyList<T>& MyList<T>::Insert(const int index, const T data)
{
    this->_IndexCheck(index);
    MyData* newData = new MyData;
    newData->data = data;
    MyData* location = this->_begin->next;
    for (int i = 0; i < index; ++i) {
        location = location->next;
    }
    newData->next = location;
    newData->previous = location->previous;
    location->previous->next = newData;
    location->previous = newData;
    this->_length++;
    return*this;
}

template<typename T>
MyList<T>& MyList<T>::Remove(const int index)
{
    if (!this->_IndexCheck(index)) {
        return*this;
    }

    MyData* location = this->_begin->next;
    for (int i = 0; i < index; ++i) {
        location = location->next;
    }
    location->previous->next = location->next;
    location->next->previous = location->previous;
    delete location;
    this->_length--;
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
        newData->data = list.GetIndex(i);
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
    return this->Add(MyList(list, length));
}

template<typename T>
MyList<T>& MyList<T>::Clear()
{
    if (this->_length == 0) {
        return*this;
    }
    MyData* location;
    for (location = this->_begin->next->next; location != this->_end; location = location->next) {
        delete location->previous;
    }
    delete this->_end->previous;
    this->_begin->next = this->_end;
    this->_end->previous = this->_begin;
    this->_length = 0;
    return*this;
}

template<typename T>
MyList<T>& MyList<T>::Sort() {

}

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
        if (this->operator[](i) == data) {
            return i;
        }
    }
    return -1;
}
