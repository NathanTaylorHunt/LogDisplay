CC = gcc
CFLAGS = -Wall

SRC_DIR = ./src
BIN_DIR = ./bin
TMP_DIR = ./tmp

HEADERS = $(wildcard $(SRC_DIR)/*.h)
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(TMP_DIR)/%.o)

TARGET = logdisplay

$(TMP_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(TARGET): $(OBJECTS)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CFLAGS)

run: $(TARGET)
	$(BIN_DIR)/$(TARGET)

clean:
	rm -f $(OBJECTS) $(BIN_DIR)/$(TARGET)
