# the compiler: gcc for C program, define as g++ for C++
CC=g++
# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS  = -g -Wall -Wextra -Wconversion -Iinclude
LDFLAGS         = "-L/the/path/to/the/curl/lib"

# The build target 
TARGET = myprogram

# all: $(TARGET)

# $(TARGET): $(TARGET).c
#     $(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

HEADERS= \
	include/Job.h \
	include/JobShop.h \
	include/Task.h \

SOURCE= \
	src/Job.cpp \
	src/JobShop.cpp \
	src/Task.cpp \
	src/Main.cpp \

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(HEADERS)
 
clean:
	rm *.o $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) -c

test: Main.o Task.h
	$(CC) $(CFLAGS) -o task.h
