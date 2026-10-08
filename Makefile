# Nom de l'exécutable
NAME = glorbFactory.exe
NAME_LIN = glordFactory

# Compilateur et flags
CC = gcc
CFLAGS = -g -I./includes
LDFLAGS = -L./lib -lraylib -lopengl32 -lgdi32 -lwinmm
LDFLAGS_LIN = lib_linux/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11

# Dossiers
SRCDIR = srcs
OBJDIR = objs
INCDIR = includes
LIBDIR = lib
LIBDIR_LIN = lib_linux

# Fichiers
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Règle principale
windows: $(NAME)
linux: $(NAME_LIN)

# Création de l'exécutable
$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(NAME_LIN): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS_LIN) -o $(NAME_LIN)

# Compilation des fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	@rm -rf $(OBJDIR)

# Nettoyage complet
fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_LIN)

# Recompilation complète
re: fclean all

.PHONY: windows linux clean fclean re