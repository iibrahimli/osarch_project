###############################
##                           ##
##    le generic makefile    ##
##   for C or C++ projects   ##
##_ _ _ _ _ _ _ _ _ _ _ _ _ _##
##                           ##
##      TODO: remove -g      ##
##                           ##
###############################

TARGET_EXEC ?= detect

BUILD_DIR ?= build
SRC_DIRS ?= src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -O3 -g
LDFLAGS ?= 

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# C sources
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

run:
	./build/$(TARGET_EXEC)

-include $(DEPS)

MKDIR_P ?= mkdir -p