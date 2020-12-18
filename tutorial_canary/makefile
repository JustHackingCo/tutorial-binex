SOURCES=$(shell ls ./src/*.c)
LDFLAGS:=-l:libvisualize.o
CFLAGS:=-no-pie
TARGET:=canary
CC:=gcc

.PHONY: all clean $(TARGET)

all: $(TARGET)

clean:
	rm -f $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) -o $(TARGET) $(CFLAGS) -I./includes -L./libs $(SOURCES) $(LDFLAGS)
