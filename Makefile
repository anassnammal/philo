NAME=philo
INCDIR=includes
SRCDIR=sources
OBJDIR=objects
HEADER=$(INCDIR)/$(NAME:=.h)
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(addprefix $(OBJDIR)/, $(notdir $(patsubst %.c, %.o, $(SOURCES))))

CCOMPILER=cc
CLIBRARY=-pthread
CFLAGS=-g -Werror -Wall -Wextra -fsanitize=thread


all: $(NAME)

$(NAME): mkd $(OBJECTS)
	$(CCOMPILER) $(CFLAGS) $^ $(CLIBRARY) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CCOMPILER) $(CFLAGS) -c $< -I $(INCDIR)/ -o $@

mkd:
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : all mkd clean fclean re
