CC = g++
CFLAGS = -static -lwiringPi -W -Wall
TARGET = edrum_raspberry
CFILE = main.cpp serial.cpp

all : 
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILE) 

clean:
	sudo rm -f $(OBJS) $(TARGET)