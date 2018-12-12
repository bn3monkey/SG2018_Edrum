sharedrum: main.o
	g++ -o $@ main.o `pkg-config gtkmm-3.0 --cflags --libs`

main.o: main.cpp
	g++ -c $*.cpp -Wall `pkg-config gtkmm-3.0 --cflags --libs`

clean:
	rm -rf *.out *.o sharedrum