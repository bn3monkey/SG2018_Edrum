#include "Hardware_IO.hpp"

Hardware_IO* Hardware_IO::instance = nullptr;

void Hardware_IO::in()
{
	while (instance->in_flag)
	{
		// read input from serial device. 
		instance->io->readSerial();

		// convert serial input to note data.
		NoteData note;
		instance->io->setSerial(&note);			

		// push note data to input queue.
		instance->queue_lock.lock();
		instance->input_queue.push(note);
		instance->queue_lock.unlock();

	}
}

void Hardware_IO::out()
{
	// only iterate when out_flag is activated.
	while (instance->out_flag)
	{
		NoteData note;

		instance->queue_lock.lock();
		//
		if (!instance->input_queue.empty())
		{
			// pop note from input_queue.
			note = instance->input_queue.front();
			instance->input_queue.pop();
			instance->queue_lock.unlock();

			// excute callback
			if(note.drum < 0 && note.drum >= np_num)
				continue; 
			printf("time = %llu drum = %d power = %d\n", note.time, note.drum, note.power);
			instance->callback_lock.lock();
			instance->callbacks[note.drum]();
			instance->callback_lock.unlock();
		}
		else
			instance->queue_lock.unlock();
	}
}

static void empty_function()
{
}

// initialize hardware_io. kick thread.
bool Hardware_IO::initialize()
{
	// if already intialize, cancel to initialize.
	if (instance != nullptr)
	{
		std::cout << "Hardware_IO already initialized" << std::endl;
		return false;
	}

	// initialize singletone instance.
	instance = new Hardware_IO();

	// initialize serial io
	instance->io = new Serial_io();
		
	// start thread.
	instance->in_flag = true;
	instance->out_flag = true;
	instance->in_thread = new std::thread(in);
	instance->out_thread = new std::thread(out);

	// initialize callbacks
	for (int i = 0; i < np_num; i++)
		instance->callbacks[i] = std::function<void()>(empty_function);
	return true;
}
// destroy hardware_io. join thread.
void Hardware_IO::destroy()
{
	instance->in_flag = false;
	instance->out_flag = false;
	instance->in_thread->join();
	instance->out_thread->join();

	delete instance->io;

	// clean queue.
	while (!instance->input_queue.empty())
		instance->input_queue.pop();

	// destroy hardware instance.
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}
// register callback.
bool Hardware_IO::registCallback(std::function<void()> callback, NoteProtocol np)
{
	// cancel if you didn't get instance.
	if (Hardware_IO::getInstance() == nullptr)
		return false;

	instance->callback_lock.lock();
	instance->callbacks[(int)np] = callback;
	instance->callback_lock.unlock();

	return true;
}

// get the sensor clock and reset sensor clock.
bool Hardware_IO::get_clock()
{
	instance->io->putSerial(nc_clock);
	return true;
}
