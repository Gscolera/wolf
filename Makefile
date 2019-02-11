NAME = wolf3d
SRC = src/*.c TgaReader/*.c
OBJ = $(SRC:.c = .o)
LINKS = -L ft_printf -lftprintf -lm 
ifeq ($(shell uname -s), Linux)
INC = -I includes -I ft_printf/includes -I TgaReader/includes
SDL = -lSDL2 -lSDL2_mixer
else
INC = -I includes -I ft_printf/includes -I TgaReader/includes -I frameworks/SDL2_mixer.framework/Versions/A/Headers \
		-I frameworks/SDL2.framework/Versions/A/Headers
SDL = -F frameworks/ -framework SDL2 -F frameworks/ -framework SDL2_mixer
endif
CC = gcc
$(NAME): $(OBJ)
	$(CC) $(OBJ) $(INC)  $(LINKS) $(SDL) -o $(NAME)
all: $(NAME)