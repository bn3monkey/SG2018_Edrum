CC = g++
CFLAGS = -std=gnu++11 -pthread -W -Wall
TARGET = Integrate

LIB1NAME = libHardWare_IO.so
LIB2NAME = libCommunicationModule.so
LIB3NAME = libResourceManager.so

CFILE = main.cpp

LIB_HW_PATH = ../edrum-hardware/Hardware_IO
LIB_CM_PATH = ../edrum-communicator
LIB_RM_PATH = ../edrum-resource_manager


all :
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILE) $(LIBFILE) -lwiringPi

integrate :
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILE) -Wl,-rpath,$(LIB_RM_PATH) -L$(LIB_RM_PATH) -lResourceManager -Wl,-rpath,$(LIB_CM_PATH) -L$(LIB_CM_PATH) -lCommunicationModule -lpython2.7 -Wl,-rpath,$(LIB_HW_PATH) -L$(LIB_HW_PATH) -lHardWare_IO -lwiringPi
	 
clean :
	sudo rm -f $(OBJS) $(TARGET)

#if you wanna use shared_library,
# First, make lib (Hardware_IO)
# Second, make lib (ResourceManager)
# Third, make integrate (Integrate) , you can change target cpp file 
