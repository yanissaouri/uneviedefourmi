# Phony targets
.PHONY: all release clean fclean re

# Toolchain and flags
CXX             = g++
CXXFLAGS        = -Wall -Wextra -Werror -g
RM              = rm -rf

# Project structure
NAME            = uneviedefourmi
BUILD_DIR       = build/
HEADER_DIR      = include
SRC_DIR         = src

# Source files
SOURCES         = $(shell find $(SRC_DIR) -name '*.cpp')
HEADERS         = $(shell find $(HEADER_DIR) -name '*.hpp' 2>/dev/null)
OBJS            = $(SOURCES:%.cpp=$(BUILD_DIR)%.o)
DEPFILES        = $(SOURCES:%.cpp=$(BUILD_DIR)%.d)

# Default target
all: $(NAME)

# Link
$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "Build successful: $(NAME)"

# Compile
$(BUILD_DIR)%.o: %.cpp $(HEADERS)
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -I$(HEADER_DIR) -MMD -MP -c $< -o $@

# Include dependency files
-include $(DEPFILES)

release: CXXFLAGS = -Wall -Wextra -Werror -O2 -DNDEBUG
release: fclean $(NAME)

clean:
	@$(RM) $(BUILD_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
