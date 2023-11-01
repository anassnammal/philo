NAME=philo
INCDIR=includes
SRCDIR=sources
OBJDIR=object
HEADER=$(INCDIR)/$(NAME:=.h)
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(addprefix $(OBJDIR)/, $(notdir $(patsubst %.c, %.o, $(SOURCES))))

CCOMPILER=cc
CLIBRARY= -pthread
CFLAGS= -g -Werror -Wall -Wextra -fsanitize=thread

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CCOMPILER) $(CFLAGS) $^ $(CLIBRARY) -o $@.out

%.o : %.c
	$(CCOMPILER) $(CFLAGS) -c $<

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re

