SOURCES=$(shell ls ./src/*.c)
LDFLAGS:=
CFLAGS:=-fno-stack-protector
TARGET:=aslr
CC:=gcc

.PHONY: all clean $(TARGET)

all: $(TARGET)

clean:
	rm -f $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) -o $(TARGET) $(CFLAGS) -I./includes $(SOURCES) $(LDFLAGS)
