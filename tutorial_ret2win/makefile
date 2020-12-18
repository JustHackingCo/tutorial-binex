SOURCES=$(wildcard ./src/*.c)
LDFLAGS:=-l:libvisualize.o
CFLAGS:=-fno-stack-protector -no-pie
TARGET:=ret2win
CC:=gcc

.PHONY: all clean $(TARGET)

all: $(TARGET)

clean:
	rm -f $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) -o $(TARGET) $(CFLAGS) -I./includes -L./libs $(SOURCES) $(LDFLAGS)
