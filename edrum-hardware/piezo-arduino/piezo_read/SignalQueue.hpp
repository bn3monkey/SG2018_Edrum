#ifndef __SIGNAL_STACK__
#define __SIGNAL_STACK__

const int QUEUE_MAXSIZE = 50;
// queue to store signal and process signal
class SignalQueue
{

protected:
    int buffer[QUEUE_MAXSIZE+1];
    int rear;

public:
    SignalQueue();
    SignalQueue(const SignalQueue& q);
    //clean buffer
    void clean();
    //check if buffer is full
    bool full();
    // push value to signal queue.
    void push(int value);
    // pop rear value in signal queue.
    int pop();
    // average value of all value in signal queue.
    int average();
    // copy data from buffer
    void copy(const char* buffer, int size);

};

#endif