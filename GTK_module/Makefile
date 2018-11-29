main : main.o gtk_module.o
	g++ -o $@.out main.o gtk_module.o `pkg-config --cflags --libs gtk+-3.0` 

main.o : main.cpp gtk_module.cpp gtk_module.hpp
	g++ -c $*.cpp `pkg-config --cflags --libs gtk+-3.0`

output.o : gtk_module.cpp gtk_module.hpp
	g++ -c $*.cpp `pkg-config --cflags --libs gtk+-3.0`

clean:
	rm -rf main.out main.o gtk_module.o

#make:
	#g++ output.cpp -o output.out `pkg-config --cflags --libs gtk+-3.0`
	#g++ main.cpp -o main.out `pkg-config --cflags --libs gtk+-3.0`
	#g++ output.backup.cpp -o output.backup.out `pkg-config --cflags --libs gtk+-3.0`
#clean:
	#rm -rf output.out

#make :
	#g++ -o main.out main.cpp output.cpp `pkg-config --cflags --libs gtk+-3.0`
