#pragma once
#include "SignalQueue.hpp"
class MovingAverageFilter : public SignalQueue
{
	
	int window;
	int half_window;

	void run(SignalQueue& q);

public:
	MovingAverageFilter(SignalQueue& q, int _window)
	{
		window = _window;
		half_window = half_window / 2;
		this->run(q);
	}
	
};