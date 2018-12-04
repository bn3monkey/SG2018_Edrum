#ifndef __SIGNAL_STACK__
#define __SIGNAL_STACK__

const int QUEUE_MAXSIZE = 50;
class SignalQueue
{
    int buffer[QUEUE_MAXSIZE+1];
    int rear;

public:
    SignalQueue()
    {
       rear = 0;
    }
    void clean()
    {
        rear = 0;
    }
    bool full()
    {
        if(rear<QUEUE_MAXSIZE)
            return false;
        else
            return true;        
    }
    void push(int value)
    {
        int i;
        for(i=0;i<rear;i++)
            this->buffer[i] = this->buffer[i+1];
        this->buffer[0] = value;
        if(!this->full())
            rear++;
    }
    int pop()
    {
        return buffer[rear-1];
    }
    int average()
    {
        int sum = 0;
        int i;
        for(i=0;i<rear;i++)
            sum += this->buffer[i];
        sum /= rear;
        return sum;
    }
    
};

#endif