main: main.o
	g++ -o $@.out main.o `pkg-config gtkmm-3.0 --cflags --libs`

main.o: main.cpp
	g++ -c $*.cpp `pkg-config gtkmm-3.0 --cflags --libs`

clean:
	rm -rf *.out *.o