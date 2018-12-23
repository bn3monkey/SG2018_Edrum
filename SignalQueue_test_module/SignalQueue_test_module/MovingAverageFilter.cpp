#include "MovingAverageFilter.hpp"
void MovingAverageFilter::run(SignalQueue& q)
{
	int temp[3 * QUEUE_MAXSIZE];
	int sum;
	int i, j;
	int start = QUEUE_MAXSIZE;
	int end = QUEUE_MAXSIZE + q.get_rear();

	for (int i = 0; i<3 * QUEUE_MAXSIZE; i++)
		temp[i] = 0;
	for (i = start; i<end; i++)
		temp[i] = q.get_buffer()[i - QUEUE_MAXSIZE];

	for (i = start; i<end; i++)
	{
		sum = 0;
		for (j = i - half_window; j < i + half_window; j++)
			sum += temp[j];
		sum /= window;
		this->buffer[i - QUEUE_MAXSIZE] = sum;
	}
	this->rear = q.get_rear();
}