CC = g++
CFLAGS = -std=gnu++11 -pthread -W -Wall
TARGET = serial_test
CFILE = test_serial.cpp serial.cpp

all :
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILE) -lwiringPi

clean :
	sudo rm -f $(OBJS) $(TARGET)
