CC = g++
CFLAGS = -std=gnu++11 -W -Wall
TARGET = ResourceManager
LIBNAME = libResourceManager.so
CFILE = main.cpp SongData.cpp SongList.cpp LocalList.cpp MyList.cpp ServerList.cpp ResourceManager.cpp
LIBFILE = SongData.cpp SongList.cpp LocalList.cpp MyList.cpp ServerList.cpp ResourceManager.cpp

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILE)

lib:
	$(CC) $(CFLAGS) -fPIC $(LIBFILE) -shared -o $(LIBNAME)

clean:
	sudo rm -f $(OBJS) $(TARGET)
