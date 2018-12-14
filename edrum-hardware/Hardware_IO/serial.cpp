#include "serial.hpp"
#include <queue>
#include <mutex>
// character queue to store charcter from serial port
std::queue<char> ch_queue;
std::mutex queue_lock;

bool continue_flag;

void Serial_io::thread_readSerial(int fd)
{
    char ch;
    // original serialGetchar() function is blocking function.
    // you have to change serial getchar function to non-blocking function.
    while(continue_flag)
    {
        if(serialDataAvail(fd))
        {
            ch = serialGetchar(fd);
	    if(ch < 10 || ch > 127)
		continue;
            //only push ASCII charecter to ch_queue
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
    // clean serial buffer
    buff->refresh();

    // store charecter from character queue to serial buffer until character is '\n' 
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
    // make serial buffer to string
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
