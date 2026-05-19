# Phony targets
.PHONY: all release clean fclean re

# Toolchain and flags
CXX      = g++
CXXFLAGS = -Wall -Wextra -Werror -g

# Project structure
HEADER_DIR = include
SRC_DIR    = src
BUILD_DIR  = build/

# OS detection
ifeq ($(OS),Windows_NT)
    EXT     := .exe
    MKDIR_P  = cmd /C if not exist "$(subst /,\,$(@D))" mkdir "$(subst /,\,$(@D))"
    SOURCES := $(subst \,/,$(shell cmd /C dir /B /S $(subst /,\,$(SRC_DIR))\*.cpp 2>nul))
    HEADERS := $(subst \,/,$(shell cmd /C dir /B /S $(subst /,\,$(HEADER_DIR))\*.hpp 2>nul))
else
    EXT     :=
    MKDIR_P  = mkdir -p $(@D)
    SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')
    HEADERS := $(shell find $(HEADER_DIR) -name '*.hpp' 2>/dev/null)
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
