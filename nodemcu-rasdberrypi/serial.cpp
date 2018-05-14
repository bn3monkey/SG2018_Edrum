#include "serial.hpp"
#include <queue>
#include <mutex>
//input thread에서 serial로 받아온 문자들을 저장하는 공간.
std::queue<char> ch_queue;
//queue의 원자성을 보존하기 위한 mutex
std::mutex queue_lock;

int Serial_io::thread_getSerial(int fd)
{
    char ch;
    while(true)
    {
        if(serialDataAvail(fd))
        {
            ch = serialGetchar(fd);
            queue_lock.lock();
            ch_queue.push(ch);
            queue_lock.unlock();
        }
    }
}

int Serial_io::getSerial()
{
    char ch;
    buff->refresh();
    //serialGetchar blocking 함수.. character 받을 떄까지 대기한다. 
    do
    {
        queue_lock.lock();
        ch = ch_queue.front();
        ch_queue.pop();
        queue_lock.unlock();
        
        buff->push(ch);
            
        //printf("%c(%d)",ch,ch);
        }
    }
    while(ch != '.');
    buff->finish();
    return 1;
}

int Serial_io::setSerial(char* tempbuf)
{
    memcpy(tempbuf, buff->data(), buff->gettop());
    //출력했으니 버퍼를 비워줌.
    return 1;
}