CC := g++
CXXFLAGS := -g -Wall -Wextra -std=c++23 -Iinclude
LDFLAGS = -lreadline -lhistory

TARGET := calc
SRC := $(wildcard src/*.cpp)
OBJ := $(patsubst src/%.cpp, build/%.o, $(SRC))

BUILD_DIR = build

$(TARGET): $(OBJ)
	$(CC) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)
