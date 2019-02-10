NAME = wolf3d
INC = -I includes -I ft_printf/includes -I TgaReader/includes
SRC = src/*.c TgaReader/*.c
OBJ = $(SRC:.c = .o)
LINKS = -L ft_printf -lftprintf -lm -lSDL2 -lSDL2_mixer
CC = gcc

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(INC)  $(LINKS) -o $(NAME)
all: $(NAME)