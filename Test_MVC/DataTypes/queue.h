//
// Created by bruno on 18/05/23.
//

#ifndef LCDTEST_QUEUE_H
#define LCDTEST_QUEUE_H

#include <cstring>

namespace bru {
template <typename T>
class queue {
private:
    T *data;
    int count;
    int capacity;
public:
    queue() : data(nullptr), count(0), capacity(1){
        data = new T[capacity];
    }
    void push(T &&x){
        if(count == capacity){
            capacity <<= 1;
            T *newData = new T[capacity];
            for(int i=0; i<count; i++){
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[count++] = x;
    }
    void push(T &x){
        if(count == capacity){
            capacity <<= 1;
            T *newData = new T[capacity];
            for(int i=0; i<count; i++){
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[count++] = x;
    }
    void pop(){
        if(count > 0){
            --count;
        }
    }
    T& front(){
        return data[count-1];
    }
    bool empty(){
        return count == 0;
    }
    int size(){
        return count;
    }
};

} // bru

#endif //LCDTEST_QUEUE_H
