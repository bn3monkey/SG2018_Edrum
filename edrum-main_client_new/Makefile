# sharedrum: main.o init.o event_handler.o
# 	g++ -o $@ main.o init.o event_handler.o `pkg-config gtkmm-3.0 --cflags --libs`

# main.o: main.cpp init.hpp
# 	g++ -c $*.cpp -Wall `pkg-config gtkmm-3.0 --cflags --libs`

# init.o: init.cpp init.hpp
# 	g++ -c $*.cpp -Wall `pkg-config gtkmm-3.0 --cflags --libs`

# event_handler.o: event_handler.cpp event_handler.hpp
# 	g++ -c $*.cpp -Wall `pkg-config gtkmm-3.0 --cflags --libs`

# clean:
# 	rm -rf *.out *.o sharedrum

CC = g++
CFLAGS = -std=gnu++11 -pthread -W -Wall
TARGET = sharedrum.out
CFILE = main.cpp init.cpp event_handler.cpp popup.cpp global_variables.cpp
HEADER = init.hpp event_handler.hpp popup.hpp global_variables.hpp
OBJS = main.o init.o event_handler.o popup.o global_variables.o

LIB_RM_PATH = ../edrum-resource_manager
LIB_CM_PATH = ../edrum-communicator

all: $(OBJS)
	@echo " > Try Build.."
	@$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) `pkg-config gtkmm-3.0 --cflags --libs` -Wl,-rpath,$(LIB_RM_PATH) -L$(LIB_RM_PATH) -lResourceManager -Wl,-rpath,$(LIB_CM_PATH) -L$(LIB_CM_PATH) -lCommunicationModule -lpython2.7
	@echo " Done."

# $(OBJS): $(CFILE) $(HEADER)
# 	@echo " > Try Compile.."
# 	@$(CC) $(CFLAGS) -c $(CFILE) `pkg-config gtkmm-3.0 --cflags --libs` -I/usr/include/python2.7

main.o: main.cpp init.hpp event_handler.hpp
	@echo " > Compile : main.o"
	@g++ -c $*.cpp -Wall `pkg-config gtkmm-3.0 --cflags --libs` -I/usr/include/python2.7

init.o: init.cpp init.hpp global_variables.hpp
	@echo " > Compile : init.o"
	@g++ -c $*.cpp -Wall `pkg-config gtkmm-3.0 --cflags --libs` -I/usr/include/python2.7

event_handler.o: event_handler.cpp event_handler.hpp init.hpp global_variables.hpp
	@echo " > Compile : event_handler.o"
	@g++ -c $*.cpp -Wall `pkg-config gtkmm-3.0 --cflags --libs` -I/usr/include/python2.7

popup.o: popup.cpp popup.hpp
	@echo " > Compile : popup.o"
	@g++ -c $*.cpp -Wall `pkg-config gtkmm-3.0 --cflags --libs`

global_variables.o: global_variables.cpp global_variables.hpp
	@echo " > Compile : global_variables.o"
	@g++ -c $*.cpp -Wall `pkg-config gtkmm-3.0 --cflags --libs` -I/usr/include/python2.7

clean:
	@echo " *** Clean up!"
	@rm -rf $(OBJS) $(TARGET)