#include <cstdio>

#include <wiringPi.h>
#include <wiringSerial.h>


typedef struct _note
{
    // 시작 시간으로부터 찍힌 노트의 시간 (milli초 단위)
    long long int msec;
    // 연주한 악기의 종류
    int drum;
    // 악기 친 세기
    int power;
} note;

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
serial_buffer buff;

//Serial에서 Protocol을 완성하는 문자열을 받을 떄까지 낱개 문자를 받는다.
int getSerial(int fd)
{
    char ch;
    buff.refresh();
    //serialGetchar blocking 함수.. character 받을 떄까지 대기한다. 
    do
    {
        ch = serialGetchar(fd)
        switch(ch)
        {
            case -1 : break;
            case default: buff(push); 
        }
    }
    while(ch == '\0');
}

int main()
{

    int serial_fd;
    //Serial port 연다.
    if ((serial_fd = serialOpen ("/dev/ttyAMA0", 115200)) < 0)  // 두번째 인자값이 보레이트 설정
    {
        fprintf (stderr, "Unable to open serial device\n") ;                   
        return 1 ;
    }
    if (wiringPiSetup() == -1)
    {
        fprintf (stdout, "Unable to start wiringPi\n") ;
        return 1 ;
    }


    while(true)
    {

    }


    return 0;
}