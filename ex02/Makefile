#------------------------------------------------------------------------------#
#                                  GENERICS                                    #
#------------------------------------------------------------------------------#

.PHONY: all bonus clean fclean re
# .SILENT:

#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

# Compiler and flags
CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98
INCLUDES    = -I$(INC_DIR)
RM          = rm -rf

# Output file name
NAME        = PmergeMe

# Directories
INC_DIR     = ./
SRCS_DIR    = ./
OBJS_DIR    = bin

# Source files
SRCS_FILES  = main.cpp  PmergeMe.cpp\

OBJS_FILES  = $(patsubst $(SRCS_DIR)%.cpp, $(OBJS_DIR)/%.o, $(SRCS_FILES))

#------------------------------------------------------------------------------#
#                                 TARGETS                                      #
#------------------------------------------------------------------------------#

all: $(NAME)

bonus: all

# Link all object files into executable
$(NAME): $(OBJS_FILES)
	$(CXX) $(CXXFLAGS) $(OBJS_FILES) -o $(NAME)
	@echo "✅ Build complete!"

# Compile each .cpp file into .o file in bin/
$(OBJS_DIR)/%.o: $(SRCS_DIR)%.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
