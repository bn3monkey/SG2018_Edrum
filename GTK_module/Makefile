sharedrum: main.o init.o
	g++ -o $@ main.o init.o `pkg-config gtkmm-3.0 --cflags --libs`

main.o: main.cpp init.hpp
	g++ -c $*.cpp -Wall `pkg-config gtkmm-3.0 --cflags --libs`

init.o: init.cpp init.hpp
	g++ -c $*.cpp -Wall `pkg-config gtkmm-3.0 --cflags --libs`

clean:
	rm -rf *.out *.o sharedrum