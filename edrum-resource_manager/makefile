CC = g++
CFLAGS = -std=gnu++11 -W -Wall
TARGET = ResourceManager
CFILE = main.cpp SongData.cpp SongList.cpp LocalList.cpp MyList.cpp ServerList.cpp ResourceManager.cpp

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILE)

clean:
	sudo rm -f $(OBJS) $(TARGET)
