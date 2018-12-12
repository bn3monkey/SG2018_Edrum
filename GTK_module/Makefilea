CC = g++
CFLAGS = -std=gnu++11 -pthread -W -Wall
TARGET = sharedrum
CFILE = main.cpp

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILE) `pkg-config gtkmm-3.0 --cflags --libs`

clean:
	sudo rm -rf $(OBJS) $(TARGET)
