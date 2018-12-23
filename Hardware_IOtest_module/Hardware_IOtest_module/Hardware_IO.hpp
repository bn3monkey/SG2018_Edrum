#ifndef __HARDWARE_IO__
#define __HARDWARE_IO__

#include <functional>
#include <queue>
#include <mutex>
#include <thread>
#include <iostream>
#include "NoteData.hpp"

//SingleTone class이다.
class Hardware_IO
{
	//Callback function을 저장하고 있는 함수 포인터 배열
	std::function<void()> callbacks[np_num];
	std::mutex callback_lock;

	// hardware에서 받아오는 input들을 보관
	std::queue<NoteData> input_queue;
	// input_queue에서 push, pop할 때 원자성을 보장해주는 동기화 객체
	std::mutex queue_lock;
	
	// thread를 받는다.
	std::thread* in_thread;
	std::thread* out_thread;

	static Hardware_IO* instance;

	// queue로 입력을 받는 메소드
	static void in();
	bool in_flag;

	// queue로 callback을 수행하는 메소드
	static void out();
	bool out_flag;

public:
	Hardware_IO() { in_flag = false; out_flag = false; }
	~Hardware_IO() {}
	
	// Singletone으로 선언된 instance를 가져온다.
	// Hardware IO를 !!!반드시!!! 초기화 후 사용한다.
	static Hardware_IO* getInstance()
	{
		return instance;
	}

	// Hardware_IO를 초기화한다. input을 받을 수 있도록 thread를 킥해준다.
	static bool initialize();
	// Hardware_IO를 정리한다. thread를 join해준다.
	static void destroy();
	
	// callback을 등록한다.
	static bool registCallback(std::function<void()> callback, NoteProtocol np);
};

#endif