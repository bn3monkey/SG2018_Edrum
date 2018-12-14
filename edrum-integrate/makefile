CC = g++
CFLAGS = -std=gnu++11 -pthread -W -Wall
TARGET = Integrate

LIB1NAME = libHardWare_IO.so
LIB2NAME = libResourceManager.so
#LIB3NAME = libIntegrate.so

CFILE = main.cpp

LIB1_PATH = /home/bn3monkey/edrum/Edrum/edrum-hardware/Hardware_IO
LIB2_PATH = /home/bn3monkey/edrum/Edrum/edrum-resource_manager
#LIB3_PATH = /home/bn3monkey/edrum/Edrum/edrum-integrate

all :
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILE) $(LIBFILE) -lwiringPi

integrate :
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILE) -Wl,-rpath,$(LIB1_PATH) -Wl,-rpath,$(LIB2_PATH) -L$(LIB1_PATH) -L$(LIB2_PATH) -lHardWare_IO -lResourceManager -lwiringPi
	 
clean :
	sudo rm -f $(OBJS) $(TARGET)

#if you wanna use shared_library,
# First, make lib (Hardware_IO)
# Second, make lib (ResourceManager)
# Third, make integrate (Integrate) , you can change target cpp file 
