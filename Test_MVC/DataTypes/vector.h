//
// Created by bruno on 18/05/23.
//

#ifndef LCDTEST_VECTOR_H
#define LCDTEST_VECTOR_H

#include <iterator>

namespace bru {

template <typename T>
class vector {
private:
    T* buffer;
    int capacity;
    int count;
#ifdef VECTOR_USE_DYNAMIC_RESIZING
    void reserve(){
        T *newData = new T[capacity];
        for(int i=0; i<count; i++){
            newData[i] = buffer[i];
        }
        delete[] buffer;
        buffer = newData;
    }
#endif
public:

    class Iterator {
    public:
        using pointer = T*;
        using reference = T&;

        explicit Iterator(pointer ptr) : ptr_(ptr) {}

        reference operator*() const {
            return *ptr_;
        }

        Iterator& operator++() {
            ++ptr_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++ptr_;
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const Iterator& other) const {
            return *this != other;
        }

    private:
        pointer ptr_;
    };

    vector() : buffer(nullptr), count(0),
#ifdef VECTOR_USE_DYNAMIC_RESIZING
    capacity(1)
#else
    capacity(16)
#endif
    {
        buffer = new T[capacity];
    }

    virtual ~vector() {
        delete[] buffer;
    }

    int size() const{
        return count;
    }

    bool empty(){
        return count == 0;
    }

    void push_back(const T &&a){
        if(count == capacity){
#ifdef VECTOR_USE_DYNAMIC_RESIZING
            capacity *= 2;
            reserve();
#else
            return;
#endif
        }
        buffer[count++] = a;
    }
    void push_back(const T &a){
        if(count == capacity){
#ifdef VECTOR_USE_DYNAMIC_RESIZING
            capacity *= 2;
            reserve();
#else
            return;
#endif
        }
        buffer[count++] = a;
    }

    void pop_back(){
        if(count > 0)
            count--;
    }

    T operator[](int index){
        return buffer[index];
    }

    Iterator begin() {
        return Iterator(buffer);
    }

    Iterator end() {
        return Iterator(buffer + count);
    }
    void clear(){
        count = 0;
    }

};

} // bru

#endif //LCDTEST_VECTOR_H
