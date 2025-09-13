# Defining the constants
CPPC = g++

TARGET_EXEC   := vsbppc
SRC_DIRS      := lnsa/src
BUILD_DIR     := build
INSTANCE_DIRS := instances/train

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

test: $(TARGET_EXEC)
	@echo "===> [TEST 1] Run without instance (expected to fail)"

	@if ./$(TARGET_EXEC) ; then                                         \
		echo "[ERROR]: program should fail without instance!"; exit 1;  \
	else                                                                \
	    echo "[SUCCESS]: failed without instance.";                     \
	fi

	@echo ""
	@echo "===> [TEST 2] Run with a random instance (Correia_Random_[1|2])"

	@INSTANCE=$$(ls $(INSTANCE_DIRS)/*Random_[12]*.txt | shuf -n 1); \
	 echo "Using : $$(basename $$INSTANCE .txt)";                    \
	if ./$(TARGET_EXEC) "$$INSTANCE" > /dev/null 2>&1 ; then         \
	    echo "[SUCCESS] ran with instance.";                         \
	else                                                             \
	    echo "[ERROR]: failed running with instance."; exit 1;       \
	fi

	@echo ""
	@echo "===> [TEST 3] Run with parameters (Correia_Random_[1|2])"

	@INSTANCE=$$(ls $(INSTANCE_DIRS)/*Random_[12]*.txt | shuf -n 1);             \
	 echo "Using: $$(basename $$INSTANCE .txt)";                                 \
	if ./$(TARGET_EXEC) "$$INSTANCE" -pa 50 -v 1 -p 0.5 > /dev/null 2>&1 ; then  \
	    echo "[SUCCESS] ran with parameters.";                                   \
	else                                                                         \
	    echo "[ERROR]: failed running with parameters."; exit 1;                 \
	fi

clean:
	rm -f $(TARGET_EXEC) $(OBJS)

.DEFAULT_GOAL := $(TARGET_EXEC)