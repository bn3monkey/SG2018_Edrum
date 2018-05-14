#define __SERIAL__
#ifndef __SERIAL__

#include <cstdio>

class serial_buffer
{
private:
    char* buffer;
    int size;
    int top;

public:
    serial_buffer(int _size = 500) : size(_size)
    {
        buffer = new char[size];
        this->top = 0;
    }
    void push(char value)
    {
        if(top == size)
        {
            fprintf(stderr, "buffer full!\n");
            return;
        }
        buffer[top++] = value;
    }
    char& operator[](int index)
    {
        return buffer[index];
    }
    char operator[](int index) const
    {
        return buffer[index];
    }
    void refresh()
    {
        this->top = 0;
    }
}

#endif