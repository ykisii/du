SOURCES = $(shell ls *.c)
OBJECTS = $(SOURCES:.c=.o)
TARGET = test

$(TARGET): $(OBJECTS)
	${CC} -o $@ $^

clean:
	rm -rf $(OBJECTS) $(TARGET)
