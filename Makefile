


NAME := FileManager.a
COMPILER := c++ -std=c++11
FLAGS := -Wall -Wextra -Werror



DIR_SRC := src/
DIR_OBJ := obj/



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

FILES_ABS_OBJ := $(addprefix $(DIR_OBJ), $(FILES_OBJ))



$(NAME) : $(FILES_ABS_OBJ)
	ar -rcs $(NAME) $(FILES_ABS_OBJ)

all:
	$(MAKE) $(FILES_ABS_OBJ)
	$(MAKE) $(NAME)

clean:
	rm -f $(FILES_ABS_OBJ)

fclean:
	$(MAKE) clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re



$(DIR_OBJ)%.o: $(DIR_SRC)%.cpp
	@mkdir -p $(dir $@)
	$(COMPILER) $(FLAGS) -Iinclude -c $^ -o $@





LIBRARYS := $(NAME)
INCLUDES := include

librarys:
	@echo $(LIBRARYS)

includes:
	@echo $(INCLUDES)

.PHONY: librarys includes


