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
TARGET = sharedrum
CFILE = main.cpp init.cpp event_handler.cpp popup.cpp
HEADER = init.hpp event_handler.hpp popup.hpp
OBJS = main.o init.o event_handler.o popup.o

LIB_RM_PATH = ../edrum-resource_manager

all: $(OBJS)
	@echo " > Try Build.."
	@$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) `pkg-config gtkmm-3.0 --cflags --libs` -Wl,-rpath,$(LIB_RM_PATH) -L$(LIB_RM_PATH) -lResourceManager
	@echo " Done."

$(OBJS): $(CFILE) $(HEADER)
	@echo " > Try Compile.."
	@$(CC) $(CFLAGS) -c $(CFILE) `pkg-config gtkmm-3.0 --cflags --libs`

clean:
	@echo " *** Clean up!"
	@rm -rf $(OBJS) $(TARGET)