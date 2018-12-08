CC = g++
CFLAGS = -std=gnu++11 -pthread -W -Wall
TARGET = HardWare_IO
CFILE = main.cpp Hardware_IO.cpp serial.cpp

all :
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILE) -lwiringPi

clean :
	sudo rm -f $(OBJS) $(TARGET)
