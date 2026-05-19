# Phony targets
.PHONY: all release clean fclean re

# Toolchain and flags
CXX      = g++
CXXFLAGS = -Wall -Wextra -Werror -g

# Project structure
HEADER_DIR = include
SRC_DIR    = src
BUILD_DIR  = build/

# Cross-platform recursive file search (no shell commands needed)
rwildcard  = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SOURCES   := $(call rwildcard,$(SRC_DIR),*.cpp)
HEADERS   := $(call rwildcard,$(HEADER_DIR),*.hpp)

# OS-specific commands
ifeq ($(OS),Windows_NT)
    EXT     := .exe
    MKDIR_P  = cmd /C mkdir "$(subst /,\,$(@D))" 2>nul
else
    EXT     :=
    MKDIR_P  = mkdir -p $(@D)
endif

NAME     = uneviedefourmi$(EXT)
OBJS     = $(SOURCES:%.cpp=$(BUILD_DIR)%.o)
DEPFILES = $(SOURCES:%.cpp=$(BUILD_DIR)%.d)

# Default target
all: $(NAME)

# Link
$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "Build successful: $(NAME)"

# Compile
$(BUILD_DIR)%.o: %.cpp $(HEADERS)
	@$(MKDIR_P)
	@$(CXX) $(CXXFLAGS) -I$(HEADER_DIR) -MMD -MP -c $< -o $@

# Include dependency files
-include $(DEPFILES)

release: CXXFLAGS = -Wall -Wextra -Werror -O2 -DNDEBUG
release: fclean $(NAME)

ifeq ($(OS),Windows_NT)
clean:
	@-cmd /C if exist build rmdir /S /Q build 2>nul

fclean: clean
	@-cmd /C if exist $(NAME) del /F /Q $(NAME) 2>nul
else
clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -f $(NAME)
endif

re: fclean all
