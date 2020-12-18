SOURCES=$(wildcard ./src/*.c)
LDFLAGS:=
CFLAGS:=-fno-stack-protector -no-pie
TARGET:=rop
CC:=gcc

.PHONY: all clean $(TARGET)

all: $(TARGET)

clean:
	rm -f $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) -o $(TARGET) $(CFLAGS) -I./includes $(SOURCES) $(LDFLAGS)
