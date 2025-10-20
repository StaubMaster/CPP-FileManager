


FANCY_NAME := FileManager
COLOR_REPO := \e[38;2;127;127;127m
COLOR_TYPE := \e[38;2;127;255;127m
COLOR_FILE := \e[38;2;127;127;255m
COLOR_NONE := \e[m

NAME := FileManager.a
COMPILER := c++ -std=c++11
FLAGS := -Wall -Wextra -Werror



FILES_CPP := \
	FilePath.cpp \
	FileInfo.cpp \
	FileMode.cpp \
	FileContext.cpp \
	DirectoryContext.cpp \
\
	Parsing/uint.cpp \
	Parsing/BitStream.cpp \
	Parsing/ByteStream.cpp \
	Parsing/LineCommand.cpp \
	Parsing/DebugManager.cpp \
\
	Format/Image.cpp \
\
	Format/PNG/Chunk.cpp \
	Format/PNG/ZLIB.cpp \
	Format/PNG/Huffman.cpp \
	Format/PNG/DEFLATE.cpp \
	Format/PNG/PNG_Filter.cpp \
	Format/PNG/PNG_IHDR.cpp \
	Format/PNG/PNG.cpp

FILES_OBJ := $(FILES_CPP:.cpp=.o)

DIR_SRC := src/
DIR_OBJ := obj/



FILES_ABS_OBJ := $(addprefix $(DIR_OBJ), $(FILES_OBJ))





################################################################

$(NAME) : $(FILES_ABS_OBJ)
#	@echo -e "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Target: $(COLOR_FILE)$@$(COLOR_NONE)"
	@echo -e "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Compiling: $(COLOR_FILE)$@$(COLOR_NONE)"
	@ar -rcs $(NAME) $(FILES_ABS_OBJ)

all:
#	@echo -e "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Target: $(COLOR_FILE)$@$(COLOR_NONE)"
	@$(MAKE) $(FILES_ABS_OBJ) -s
	@$(MAKE) $(NAME) -s

clean:
#	@echo -e "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Target: $(COLOR_FILE)$@$(COLOR_NONE)"
	@rm -f $(FILES_ABS_OBJ)

fclean:
#	@echo -e "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Target: $(COLOR_FILE)$@$(COLOR_NONE)"
	@$(MAKE) clean -s
	@rm -f $(NAME)

re:
#	@echo -e "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Target: $(COLOR_FILE)$@$(COLOR_NONE)"
	@$(MAKE) fclean -s
	@$(MAKE) all -s

.PHONY: all clean fclean re

################################################################





$(DIR_OBJ)%.o: $(DIR_SRC)%.cpp
	@echo -e "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Compiling: $(COLOR_FILE)$@$(COLOR_NONE)"
	@mkdir -p $(dir $@)
	@$(COMPILER) $(FLAGS) $(foreach include, $(INCLUDES), -I$(include)) -c $^ -o $@





################################################################

LIBRARYS := $(NAME)
INCLUDES := include

librarys:
	@echo $(LIBRARYS)

includes:
	@echo $(INCLUDES)

.PHONY: librarys includes

################################################################


