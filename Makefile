# Set the compiler
CPPC = g++

TARGET_EXEC := vsbppc.exe
SRC_DIRS := src
INSTANCE_DIRS := instances

# Find all the C++ files we want to compile
SRCS := $(shell dir /s /b $(SRC_DIRS)\*.cpp)

# Find all instances
INSTANCES :=  $(shell dir /s /b $(INSTANCE_DIRS)\*.txt)

# The final build step
$(TARGET_EXEC):
	$(CPPC) $(SRCS) -o $@

run: $(INSTANCES) $(TARGET_EXEC)
	$(foreach instance, $(INSTANCES), $(TARGET_EXEC) "$(instance)" &&) true

clean:
	del $(TARGET_EXEC)

.DEFAULT_GOAL := $(TARGET_EXEC)