CC = g++
CFLAGS = -std=gnu++11 -pthread -W -Wall
TARGET = HardWare_IO
LIBNAME = libHardWare_IO.so
CFILE = main.cpp
LIBFILE = Hardware_IO.cpp serial.cpp
LIBPATH = ../../edrum-hardware/Hardware_IO

all :
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILE) $(LIBFILE) -lwiringPi

lib :
	$(CC) $(CFLAGS) -fPIC $(LIBFILE) -shared -o $(LIBNAME) -lwiringPi

libtest :
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILE) -Wl,-rpath,$(LIBPATH) -L$(LIBPATH) -lHardWare_IO -lwiringPi
	 
clean :
	sudo rm -f $(OBJS) $(TARGET)
