NAME=philo
INCDIR=includes
SRCDIR=sources
OBJDIR=objects
HEADER=$(INCDIR)/$(NAME:=.h)
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(addprefix $(OBJDIR)/, $(notdir $(patsubst %.c, %.o, $(SOURCES))))

CCOMPILER=cc
CLIBRARY=-pthread
CFLAGS=-g -Werror -Wall -Wextra #-fsanitize=thread


all: $(NAME)

$(NAME): $(OBJDIR) $(OBJECTS)
	$(CCOMPILER) $(CFLAGS) $(OBJECTS) $(CLIBRARY) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	$(CCOMPILER) $(CFLAGS) -c $< -I $(INCDIR)/ -o $@

$(OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re
