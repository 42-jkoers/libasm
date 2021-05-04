NAME = libasm.a

NA = nasm

NFLAGS = -f macho64
# NFLAGS = -f elf64

SRC = ft_read.s \
ft_strcmp.s \
ft_strcpy.s \
ft_strdup.s \
ft_strlen.s \
ft_write.s \

OBJ = $(SRC:.s=.o)

# I hate Make so much
.SUFFIXES:

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $^
	ranlib $(NAME)

%.o: %.s
	$(NA) $(NFLAGS) $<

clean:
	rm -f $(OBJ)
	rm -f ./testor

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
	gcc libasm.a test/main.c -o testor
	./testor

.PHONY: all re clean fclean test
