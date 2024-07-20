# Defining the constants
CPPC = g++

TARGET_EXEC   := vsbppc
SRC_DIRS      := src
BUILD_DIR     := build
INSTANCE_DIRS := instances/set1_100

# Find all the C++ files
# Create a list of object files
# Find all instances
SRCS      := $(shell find $(SRC_DIRS) -name '*.cpp')
OBJS      := $(SRCS:$(SRC_DIRS)/%.cpp=$(BUILD_DIR)/%.o)
INSTANCES := $(shell find $(INSTANCE_DIRS) -name '*.txt')

# The final build step
$(TARGET_EXEC): $(OBJS)
	$(CPPC) $(OBJS) -o $@

# Rule to create object files
$(BUILD_DIR)/%.o: $(SRC_DIRS)/%.cpp
	$(CPPC) -c $< -o $@

run_all: $(INSTANCES) $(TARGET_EXEC)
	@for instance in $(INSTANCES); do                       \
		BASENAME=$$(basename $$instance .txt);              \
		INSTANCE_PART=$$(echo $$BASENAME | cut -d'_' -f3-); \
		echo "";                                            \
		echo "***Running $$INSTANCE_PART***";               \
		if [ -z "$(OUTPUT_FILE)" ]; then                    \
			./$(TARGET_EXEC) "$$instance";                  \
		else                                                \
			./$(TARGET_EXEC) "$$instance" "$(OUTPUT_FILE)"; \
		fi;                                                 \
	done

clean:
	rm -f $(TARGET_EXEC) $(OBJS)

.DEFAULT_GOAL := $(TARGET_EXEC)