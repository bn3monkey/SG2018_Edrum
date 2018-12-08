#pragma warning(disable : 4996)
#include "Hardware_IO.hpp"
#include <conio.h>

Hardware_IO* Hardware_IO::instance = nullptr;

void Hardware_IO::in()
{
	while (instance->in_flag)
	{
		//1. 외부 장비로부터 입력을 받아온다. 
		char buffer = 0;
		if (kbhit())
			buffer = getch();

		if (!buffer) continue;

		//2. 받아온 입력을 note로 만들어 Queue에 넣어준다.
		NoteData note;
		note.time = 0;
		note.power = 0;
		switch (buffer)
		{
		case 'w': note.power = np_up; break;
		case 's': note.power = np_down; break;
		case 'a': note.power = np_left; break;
		case 'd': note.power = np_right; break;
		case ' ': note.power = np_ok; break;
		case 'q': note.power = np_none; break;
		default: note.power = np_idle; break;
			
		}

		// note를 input_queue에 넣는다.
		instance->queue_lock.lock();
		instance->input_queue.push(note);
		instance->queue_lock.unlock();

	}
}

void Hardware_IO::out()
{
	while (instance->out_flag)
	{
		NoteData note;

		instance->queue_lock.lock();
		if (!instance->input_queue.empty())
		{
			// note를 input_queue에 빼온다.
			note = instance->input_queue.front();
			instance->input_queue.pop();
			instance->queue_lock.unlock();

			//callback을 수행한다.
			instance->callback_lock.lock();
			instance->callbacks[note.power]();
			instance->callback_lock.unlock();
		}
		else
			instance->queue_lock.unlock();
	}
}

static void empty_function()
{
}

// Hardware_IO를 초기화한다. input을 받을 수 있도록 thread를 킥해준다.
bool Hardware_IO::initialize()
{
	// 이미 초기화되었으면, 초기화를 멈춘다.
	if (instance != nullptr)
	{
		std::cout << "Hardware_IO already initialized" << std::endl;
		return false;
	}

	// SingleTone 객체를 초기화한다.
	instance = new Hardware_IO();
	
	// thread를 시작한다.
	instance->in_flag = true;
	instance->out_flag = true;
	instance->in_thread = new std::thread(in);
	instance->out_thread = new std::thread(out);

	// 오류를 막기 위해, 함수 테이블을 empty function으로 초기화한다.
	for (int i = 0; i < np_num; i++)
		instance->callbacks[i] = std::function<void()>(empty_function);

	return true;
}
// Hardware_IO를 정리한다. thread를 join해준다.
void Hardware_IO::destroy()
{
	instance->in_flag = false;
	instance->out_flag = false;
	instance->in_thread->join();
	instance->out_thread->join();

	//queue를 비운다.
	while (!instance->input_queue.empty())
		instance->input_queue.pop();

	// SingleTone 객체를 할당해제한다.
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}
// callback을 등록한다.
bool Hardware_IO::registCallback(std::function<void()> callback, NoteProtocol np)
{
	// SingleTone으로 선언하지 않았으면 취소한다.
	if (Hardware_IO::getInstance() == nullptr)
		return false;

	instance->callback_lock.lock();
	instance->callbacks[(int)np] = callback;
	instance->callback_lock.unlock();

	return true;
}