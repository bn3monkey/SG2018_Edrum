#include "SignalQueue.hpp"
SignalQueue::SignalQueue()
{
    rear = 0;
}
SignalQueue::SignalQueue(const SignalQueue& q)
{
    this->rear = q.rear;
    for(int i=0;i<rear;i++)
    {
        this->buffer[i] = q.buffer[i];
    }
}
void SignalQueue::clean()
{
    rear = 0;
}
bool SignalQueue::full()
{
    if(rear<QUEUE_MAXSIZE)
        return false;
    else
        return true;        
}
void SignalQueue::push(int value)
{
    int i;
    for (i = rear-1; i>=0; i--)
        this->buffer[i+1] = this->buffer[i];
    this->buffer[0] = value;
    if (!this->full())
        rear++;
}
int SignalQueue::pop()
{
    return buffer[rear-1];
}
int SignalQueue::average()
{
    unsigned long sum = 0;
    int i;
    for(i=0;i<rear;i++)
        sum += this->buffer[i];
    sum /= rear;
    return sum;
}
void SignalQueue::copy(const char* buffer, int size)
{
    if(size > QUEUE_MAXSIZE)
        return;
    for(int i=0;i<size;i++)
        this->buffer[i] = buffer[i];
}
