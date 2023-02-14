//
// Created by bleppe on 08/02/23.
//

#ifndef READER_TESTCLASS_H
#define READER_TESTCLASS_H


class TestClass{

private:
    int a;
    int b;
    int c;

public:

    TestClass(int a, int b, int c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    int sum() const
    {
        return a+b+c;
    }

};


#endif //READER_TESTCLASS_H
