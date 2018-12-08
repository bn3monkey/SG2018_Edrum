#include "Hardware_IO.hpp"
#include "TestModule.hpp"

#include <condition_variable>

std::mutex m;
std::condition_variable cv;

int main()
{
	Hardware_IO::initialize();
	
	IOTestModule pTest;
	std::function<void()> container;
	
	// [&사용하는 객체 변수명] () { 실제로 넣으려는 함수(); }
	
	container = [&pTest]() {pTest.up();};
	Hardware_IO::registCallback(container, np_up);
	// class 내부에서 불러오는 경우, 
	// Hardware_IO::registerCallback( [&this]() {pTest.up();}, np_up );
	// 위와 같은 식으로 사용하면 된다.

	container = [&pTest]() {pTest.down(); Hardware_IO::get_clock();};
	Hardware_IO::registCallback(container, np_down);
	container = [&pTest]() {pTest.left(); };
	Hardware_IO::registCallback(container, np_left);
	container = [&pTest]() {pTest.right(); };
	Hardware_IO::registCallback(container, np_right);
	//container = [&pTest]() {pTest.ok(); };
	//Hardware_IO::registCallback(container, np_ok);
	
	container = []() {
		std::unique_lock<std::mutex> lk(m);
		lk.unlock();
		cv.notify_all();
		printf("End!\n");
	};
	Hardware_IO::registCallback(container, np_ok);

	Hardware_IO::registCallback([](){cout<<"reset clock!" << endl;}, np_cmd_clock);

	
	std::unique_lock<std::mutex> lk(m);
	cv.wait(lk);

	Hardware_IO::destroy();
}
