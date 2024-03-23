COMPILER = gcc
COMPILER_FLAGS = -Wall -Wextra -pedantic-errors
INCLUDE_PATH = -I include/
OBJECT_FILES = ./*.o
TARGET = jpgVal
INSTALL_PATH = /usr/local

all : $(TARGET)

$(TARGET): object
	$(COMPILER) -o $@ $(OBJECT_FILES)

object:
	$(COMPILER) $(COMPILER_FLAGS) $(INCLUDE_PATH) -c src/*.c

install: $(TARGET)
	install -m755 $(TARGET) $(INSTALL_PATH)/bin

clean:
	rm -f $(OBJECT_FILES) $(TARGET)

uninstall:
	rm -f $(INSTALL_PATH)/bin/$(TARGET)
