sharedrum: main.o init.o event_handler.o
	g++ -o $@ main.o init.o event_handler.o `pkg-config gtkmm-3.0 --cflags --libs`

main.o: main.cpp init.hpp
	g++ -c $*.cpp -Wall `pkg-config gtkmm-3.0 --cflags --libs`

init.o: init.cpp init.hpp
	g++ -c $*.cpp -Wall `pkg-config gtkmm-3.0 --cflags --libs`

event_handler.o: event_handler.cpp event_handler.hpp
	g++ -c $*.cpp -Wall `pkg-config gtkmm-3.0 --cflags --libs`

clean:
	rm -rf *.out *.o sharedrum