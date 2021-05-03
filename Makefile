NAME = libasm.a

NA = nasm

NFLAGS = -f macho64
# NFLAGS = -f elf64


SRC = ft_read.asm \
ft_strcmp.asm \
ft_strcpy.asm \
ft_strdup.asm \
ft_strlen.asm \
ft_write.asm \

OBJ = $(SRC:.asm=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $^
	ranlib $(NAME)

%.o: %.asm
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

.PHONY: all re clean fclean test bonus
