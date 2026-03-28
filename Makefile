CC := g++
CXXFLAGS := -g -Wall -Wextra -std=c++23 -Iinclude
LDFLAGS = -lreadline -lhistory

TARGET := calc
SRC := $(wildcard src/*.cpp)
OBJ := $(patsubst src/%.cpp, build/%.o, $(SRC))

CONFIG_DIR := $(HOME)/.config/calc
CONFIG_FILE := $(CONFIG_DIR)/calc.conf

BUILD_DIR = build

$(TARGET): $(OBJ)
	$(CC) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

install: $(TARGET)
	sudo cp $(TARGET) /usr/bin/
	mkdir -p "$(CONFIG_DIR)"
	[ -f "$(CONFIG_FILE)" ] || echo "# calc configuration" > "$(CONFIG_FILE)"

uninstall:
	sudo rm -f /usr/bin/$(TARGET)
	rm -rf "$(CONFIG_DIR)"

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)
