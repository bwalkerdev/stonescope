TARGET = stonescope 
SRC_FILES = ./src/main.cpp ./include/TouchstoneFile.cpp ./include/TSPlot.cpp ./include/Axis.cpp ./include/Line.cpp ./include/CLIParser.cpp

# NO EDITS NEEDED BELOW THIS LINE

CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic-errors # -Werror 
CXXFLAGS_DEBUG = -g
CXXVERSION = -std=c++17

OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(OS),Windows_NT)
	TARGET := $(TARGET).exe
	DEL = del
	Q =

	INC_PATH = Z:/CSCI200/include/
	LIB_PATH = Z:/CSCI200/lib/

	ARCH = 
	RPATH =
else
	DEL = rm -f
	Q = "

	INC_PATH = /usr/local/include/
	LIB_PATH = /usr/local/lib/

	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CXXFLAGS += -D LINUX
		RPATH =
	endif
	ifeq ($(UNAME_S),Darwin)
		TARGET_MAKEFILE = Makefile.osx
		CXXFLAGS += -D OSX
		RPATH = -Wl,-rpath,/Library/Frameworks
	endif

	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		ARCH = 
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		ARCH = 
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		ARCH = 
	endif
endif

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(ARCH) -o $@ $^ $(RPATH) -L$(LIB_PATH) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_DEBUG) $(ARCH) $(CXXVERSION) -o $@ -c $< -I$(INC_PATH) 

clean:
	$(DEL) $(TARGET) $(OBJECTS)
	
depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) -MM $(SRC_FILES) >> Makefile

.PHONY: all clean depend

# DEPENDENCIES
main.o: main.cpp ./include/TouchstoneFile.h ./include/CLIParser.h
TouchstoneFile.o: ./include/TouchstoneFile.cpp ./include/TouchstoneFile.h ./include/DataPoint.h ./include/Options.h
TSPlot.o: /.include/TSPlot.cpp ./include/TSPlot.h ./include/Axis.h ./include/Line.h
Axis.o: ./include/Axis.cpp ./include/Axis.h
Line.o: ./include/Line.cpp  ./include/Line.h
CLIParser.o: ./include/CLIParser.cpp ./include/CLIParser.h
