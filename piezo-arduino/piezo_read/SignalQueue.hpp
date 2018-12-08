#ifndef __SIGNAL_STACK__
#define __SIGNAL_STACK__

const int QUEUE_MAXSIZE = 50;
class SignalQueue
{

protected:
    int buffer[QUEUE_MAXSIZE+1];
    int rear;

public:
    SignalQueue()
    {
       rear = 0;
    }
    SignalQueue(const SignalQueue& q)
    {
        this->rear = q.rear;
        for(int i=0;i<rear;i++)
        {
            this->buffer[i] = q.buffer[i];
        }
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
		for (i = rear-1; i>=0; i--)
			this->buffer[i+1] = this->buffer[i];
		this->buffer[0] = value;
		if (!this->full())
			rear++;
    }
    int pop()
    {
        return buffer[rear-1];
    }
    int average()
    {
        unsigned long sum = 0;
        int i;
        for(i=0;i<rear;i++)
            sum += this->buffer[i];
        sum /= rear;
        return sum;
    }
    void copy(const char* buffer, int size)
    {
        if(size > QUEUE_MAXSIZE)
            return;
        for(int i=0;i<size;i++)
            this->buffer[i] = buffer[i];
    }

};

#endif
