SOURCES=$(wildcard ./src/*.c)
LDFLAGS:=-l:libvisualize.o
CFLAGS:=-fno-stack-protector -z execstack
TARGET:=shellcode
CC:=gcc

.PHONY: all clean $(TARGET)

all: $(TARGET)

clean:
	rm -f $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) -o $(TARGET) $(CFLAGS) -I./includes -L./libs $(SOURCES) $(LDFLAGS)
