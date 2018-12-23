CC = g++
CFLAGS = -std=gnu++11 -pthread -W -Wall
TARGET = cm.out
LIBNAME = libCommunicationModule.so
CFILE = main.cpp
LIBFILE = CommunicationModule.cpp ../edrum-resource_manager/SongData.cpp
LIBPATH = ../edrum-communicator/

all :
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILE) $(LIBFILE) -I/usr/include/python2.7 -lpython2.7

lib :
	$(CC) $(CFLAGS) -fPIC $(LIBFILE) -shared -o $(LIBNAME) -Wl,-rpath,$(LIBPATH) -I/usr/include/python2.7 -lpython2.7

libtest :
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILE) -Wl,-rpath,$(LIBPATH) -L$(LIBPATH) -lCommunicationModule -I/usr/include/python2.7 -lpython2.7
	 
clean :
	sudo rm -f $(OBJS) $(TARGET) $(LIBNAME)
