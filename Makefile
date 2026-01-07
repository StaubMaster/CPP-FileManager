


################################################################
#                           OS Stuff                           #
################################################################

ifeq ($(OS), Windows_NT)
	CheckOS := Windows
else
	CheckOS := $(shell uname -s)
endif

FANCY_NAME := FileManager

ifeq ($(CheckOS), Windows)

FANCY_ECHO := echo -e
COLOR_REPO := \e[38;2;127;127;127m
COLOR_TYPE := \e[38;2;127;255;127m
COLOR_FILE := \e[38;2;127;127;255m
COLOR_NONE := \e[m

endif

ifeq ($(CheckOS), Darwin)

FANCY_ECHO := echo
COLOR_REPO := \033[38;2;127;127;127m
COLOR_TYPE := \033[38;2;127;255;127m
COLOR_FILE := \033[38;2;127;127;255m
COLOR_NONE := \033[m

endif

################################################################



NAME := FileManager.a
#COMPILER := c++ -std=c++11
COMPILER := g++ -g -std=c++11
FLAGS := -Wall -Wextra -Werror



FILES_CPP := \
	FilePath.cpp \
	FilePathSegment.cpp \
	FilePathSegmentCollection.cpp \
	FileMode.cpp \
	FileSystemStat.cpp \
	FileSystemInfo.cpp \
	FileContext.cpp \
	DirectoryContext.cpp \
	FileException.cpp \
\
	Parsing/uint.cpp \
	Parsing/BitStream.cpp \
	Parsing/ByteStream.cpp \
	Parsing/LineCommand.cpp \
	Parsing/DebugManager.cpp \
	Parsing/StringHelp.cpp \
	Parsing/ExceptionBase.cpp \
	Parsing/CountCheck.cpp \
	Parsing/ParsingCommand.cpp \
\
	Format/PNG/Chunk.cpp \
	Format/PNG/ZLIB.cpp \
	Format/PNG/Huffman.cpp \
	Format/PNG/DEFLATE.cpp \
	Format/PNG/PNG_Filter.cpp \
	Format/PNG/PNG_IHDR.cpp \
	Format/PNG/PNG.cpp \
\
	Format/ColorU4.cpp \
	Format/Image.cpp

FILES_OBJ := $(FILES_CPP:.cpp=.o)

DIR_SRC := src/
DIR_OBJ := obj/



FILES_ABS_OBJ := $(addprefix $(DIR_OBJ), $(FILES_OBJ))





################################################################

all:
#	@$(FANCY_ECHO) "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Target: $(COLOR_FILE)$@$(COLOR_NONE)"
	@$(MAKE) $(FILES_ABS_OBJ) -s
	@$(MAKE) $(NAME) -s

clean:
#	@$(FANCY_ECHO) "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Target: $(COLOR_FILE)$@$(COLOR_NONE)"
	@rm -f $(FILES_ABS_OBJ)

fclean:
#	@$(FANCY_ECHO) "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Target: $(COLOR_FILE)$@$(COLOR_NONE)"
	@$(MAKE) clean -s
	@rm -f $(NAME)

re:
#	@$(FANCY_ECHO) "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Target: $(COLOR_FILE)$@$(COLOR_NONE)"
	@$(MAKE) fclean -s
	@$(MAKE) all -s

.PHONY: all clean fclean re

$(NAME) : $(FILES_ABS_OBJ)
#	@$(FANCY_ECHO) "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Target: $(COLOR_FILE)$@$(COLOR_NONE)"
#	@$(FANCY_ECHO) "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Compiling: $(COLOR_FILE)$@$(COLOR_NONE)"
	@ar -rcs $(NAME) $(FILES_ABS_OBJ)

################################################################





$(DIR_OBJ)%.o: $(DIR_SRC)%.cpp
	@$(FANCY_ECHO) "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Compiling: $(COLOR_FILE)$@$(COLOR_NONE)"
	@mkdir -p $(dir $@)
	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -c $^ -o $@





################################################################

LIBRARYS := $(NAME)
INCLUDES := include
ARGUMENTS := 

ARGS_LIBRARYS = $(foreach library,$(LIBRARYS),$(library))
ARGS_INCLUDES = $(foreach include, $(INCLUDES),-I$(include))

librarys:
	@echo $(LIBRARYS)

includes:
	@echo $(INCLUDES)

arguments:
	@echo $(ARGUMENTS)

.PHONY: librarys includes arguments

################################################################





################################################################

EXE = test.exe

test: $(FILES_ABS_OBJ)
	$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -o $(EXE) mainDir0.cpp $(FILES_ABS_OBJ)

test_clean:
	rm -f $(EXE)

.PHONY: test test_clean

################################################################
