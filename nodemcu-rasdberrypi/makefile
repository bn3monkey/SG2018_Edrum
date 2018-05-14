CC = g++
CFLAGS = -std=c++11 -W -Wall
TARGET = edrum_raspberry
CFILE = main.cpp serial.cpp

all : 
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILE) -lwiringPi

clean:
	sudo rm -f $(OBJS) $(TARGET)
