#ifndef __HARDWARE_IO__
#define __HARDWARE_IO__

#include <functional>
#include <queue>
#include <mutex>
#include <thread>
#include <iostream>
#include "serial.hpp"

// SingleTon class to hardware_io.
// you can register callback function to hardware_IO
class Hardware_IO
{
	//Callback function array
	std::function<void()> callbacks[np_num];
	std::mutex callback_lock;

	// input queue to store hardware input
	std::queue<NoteData> input_queue;
	std::mutex queue_lock;
	
	static Hardware_IO* instance;

	// thread to push hardware input 
	std::thread* in_thread;
	static void in();
	bool in_flag;

	// thread to execute callback function
	std::thread* out_thread;
	static void out();
	bool out_flag;

	// class instance to read serial input and output
	Serial_io* io;

public:
	Hardware_IO() { in_flag = false; out_flag = false; }
	~Hardware_IO() {}
	
	// get singleton instance
	// You 'must' execute initialize() function before using getInstance() function 
	static Hardware_IO* getInstance()
	{
		return instance;
	}

	// initialize hardware_io instance. kick threads
	static bool initialize();
	// destroy hardware_io instance join threads.
	static void destroy();
	
	// register callback.
	static bool registCallback(std::function<void()> callback, NoteProtocol np);
	// get arduino clock and initialize arduino clock.
	static bool get_clock();
};

#endif
