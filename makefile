###############################
##                           ##
##    le generic makefile    ##
##   for C or C++ projects   ##
##_ _ _ _ _ _ _ _ _ _ _ _ _ _##
##                           ##
##      TODO: remove -g      ##
##                           ##
###############################

TARGET_EXEC ?= detecter

BUILD_DIR ?= build
SRC_DIRS ?= src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -O3 -Wall
LDFLAGS ?= 

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# C sources
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) -c $< -o $@

.PHONY: clean test

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r cov test_logs
run:
	./build/$(TARGET_EXEC)

-include $(DEPS)

test: coverage 
	cp $(BUILD_DIR)/$(TARGET_EXEC) .
	./test.sh
	rm $(TARGET_EXEC)

generate_coverage: test
	$(MKDIR_P) cov_html
	gcovr --html --html-details -r . -o cov.html
	mv *.html cov_html

coverage: CPPFLAGS = $(INC_FLAGS) -g -O0 -fprofile-arcs -ftest-coverage
coverage: LDFLAGS =  -fprofile-arcs -ftest-coverage
coverage: clean $(BUILD_DIR)/$(TARGET_EXEC)

MKDIR_P ?= mkdir -p