CC = g++
CFLAGS = -std=gnu++11 -pthread -W -Wall
TARGET = edrum_raspberry
CFILE = main.cpp serial.cpp record.cpp play.cpp

all : 
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILE) -lwiringPi

clean:
	sudo rm -f $(OBJS) $(TARGET)
