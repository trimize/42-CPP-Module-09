NAME = btc
SRCSDIR = ./
OBJDIR = ./objs/

SOURCES = $(wildcard $(SRCSDIR)*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

C++ = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(addprefix $(OBJDIR), $(OBJECTS))
	@$(C++) $(CFLAGS) -o $@ $^
	@echo "$@ has been successfully built!"

$(OBJDIR)%.o: $(SRCSDIR)%.cpp | $(OBJDIR)
	@$(C++) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@echo "Cleaning objects"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "Cleaning $(NAME)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re