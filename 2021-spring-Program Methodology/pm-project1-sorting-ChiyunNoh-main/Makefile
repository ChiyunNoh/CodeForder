CC = g++
CFLAGS = -W -Wall
CCFLAGS= -Og
TARGET = sort
OBJECTS = main.o sort.o

all : $(TARGET)

$(OBJECTS): %.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGET) : $(OBJECTS) 
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o $(TARGET)

test : 
	for length in 4 16 64 256 512 2048 8192 32768 ; do \
			echo "======== [Sort Tests] : length $$length =======\n" && \
			./sort $$length; \
	done
