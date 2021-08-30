CC = g++
CFLAGS = -W
CCFLAGS= -Og
TARGET = game_file
OBJECTS = main.o poke_DS.o

all : $(TARGET)

$(OBJECTS): %.o : %.cpp
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o $(TARGET)