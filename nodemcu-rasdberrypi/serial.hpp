//#define __SERIAL__
#ifndef __SERIAL__

#include <cstdio>

class Serial_buffer
{
private:
    char* buffer;
    int size;
    int top;

public:
    Serial_buffer(int _size = 500) : size(_size)
    {
        buffer = new char[size];
        this->top = 0;
    }
    inline void push(char value)
    {
        if(top == size)
        {
            fprintf(stderr, "buffer full!\n");
            return;
        }
        buffer[top++] = value;
    }
    inline int gettop() {return this->top;}
    inline char*& data() {return this->data;}

    char& operator[](int index)
    {
        return buffer[index];
    }
    char operator[](int index) const
    {
        return buffer[index];
    }
    inline void refresh()
    {
        this->top = 0;
    }
};

class Serial_io
{
    Serial_buffer* buff;
    public:
    Serial_io()
    {
        buff = new serial_buffer(100);
    }
    ~Serial_io()
    {
        if(buff != NULL)
            delete buff;
    }

    //Serial에서 Protocol을 완성하는 문자열을 받을 떄까지 낱개 문자를 받는다.
    int getSerial(int fd);
    //Serial에서 받은 문자열을 parameter로 넘어온 버퍼에 저장한다.
    int setSerial(char* tempbuf);
};
#endif