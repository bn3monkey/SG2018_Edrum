#include "serial.hpp"
#include <queue>
#include <mutex>
//input thread에서 serial로 받아온 문자들을 저장하는 공간.
std::queue<char> ch_queue;
//queue의 원자성을 보존하기 위한 mutex
std::mutex queue_lock;

bool continue_flag;

void Serial_io::thread_readSerial(int fd)
{
    char ch;
    //serialGetchar blocking 함수.. character 받을 떄까지 대기한다. 
    //wiringSerial Device driver를 건드려서 non-blocking으로 바꾸었다.
    while(continue_flag)
    {
        if(serialDataAvail(fd))
        {
            ch = serialGetchar(fd);
	    if(ch < 10 || ch > 127)
		continue;
            queue_lock.lock();
            ch_queue.push(ch);
            queue_lock.unlock();
       } 
    }
}

int Serial_io::readSerial()
{
    bool exists;
    char ch = 0;
    buff->refresh();
    while(ch != '\n')
    {
	exists = false;
        queue_lock.lock();
        if(!ch_queue.empty())
	{
		exists = true;
		ch = ch_queue.front();
        	ch_queue.pop();
	}
        queue_lock.unlock();
        
	    if(exists)
	    {
        	buff->push(ch);
         	//printf("%c(%d)\n",ch,ch);
	    }
    }
    buff->finish();
    //printf("blocking test : %s\n", buff->data());
    return 1;
}

int Serial_io::setSerial(NoteData* pnote)
{

    //printf("blocking test : %s %d\n", buff->data(), buff->gettop());
    sscanf(buff->data(), "%llu %d %d", &(pnote->time), &(pnote->drum), &(pnote->power));

    return 1;
}
int Serial_io::putSerial(char buf)
{
    serialPutchar(this->serial_fd, buf);
    return 1;
}
int Serial_io::writeSerial(char* buf)
{
    serialPuts(this->serial_fd, buf);
    return 1;
}
int Serial_io::writeNote(NoteData note)
{
    char buf[30];
    sprintf(buf,"%llu %d %d\n",note.time, note.drum, note.power);
    return writeSerial(buf);
}

int Serial_io::cleanSerial()
{
    this->buff->refresh();
    return 1;
}
