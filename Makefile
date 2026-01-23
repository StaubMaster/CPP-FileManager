
NAME := FileManager.a

COMPILER := g++ -g -std=c++11
FLAGS := -Wall -Wextra -Werror
ARCHIVER := ar -rcs
REMOVER := rm -f

FANCY_NAME := FileManager
include fancy.mk



DIR_SRC := src/
DIR_OBJ := obj/



FILES_CPP := \
	FilePath.cpp \
	FilePathSegment.cpp \
	FilePathSegmentCollection.cpp \
	FileMode.cpp \
	FileSystemStat.cpp \
	FileSystemInfo.cpp \
	FileInfo.cpp \
	DirectoryInfo.cpp \
	TextExceptionBase.cpp \
	FileExceptions.cpp \
\
	FileParsing/BitStream.cpp \
	FileParsing/ByteStream.cpp \
	FileParsing/LineCommand.cpp \
	FileParsing/DebugManager.cpp \
	FileParsing/StringHelp.cpp \
	FileParsing/ExceptionBase.cpp \
	FileParsing/CountCheck.cpp \
	FileParsing/ParsingCommand.cpp \
\
	FileParsing/Text/Exceptions.cpp \
	FileParsing/Text/LineStream.cpp \
	FileParsing/Text/TextCommand.cpp \
	FileParsing/Text/TextCommandStream.cpp \
\
	FileFormat/PNG/ErrorDetection.cpp \
	FileFormat/PNG/Chunk.cpp \
	FileFormat/PNG/ZLIB.cpp \
	FileFormat/PNG/Huffman.cpp \
	FileFormat/PNG/DEFLATE.cpp \
	FileFormat/PNG/Filter.cpp \
	FileFormat/PNG/IHDR.cpp \
	FileFormat/PNG/PNG.cpp \
\
	ValueType/Bool2D.cpp \
	ValueType/Undex2D.cpp \
	ValueType/UndexBox2D.cpp \
	ValueType/UndexLoop2D.cpp \
	ValueType/ColorU4.cpp \
	ValueType/uint.cpp \
\
	Image.cpp

FILES_OBJ := $(FILES_CPP:.cpp=.o)

FILES_ABS_OBJ := $(addprefix $(DIR_OBJ), $(FILES_OBJ))





################################################################

all:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s $(FILES_ABS_OBJ)
	@$(MAKE) -s $(NAME)

clean:
	@$(call fancyNameTargetEcho,$@)
	@$(REMOVER) $(FILES_ABS_OBJ)

fclean:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s clean
	@$(REMOVER) $(NAME)

re:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s fclean
	@$(MAKE) -s all

.PHONY: all clean fclean re

$(NAME) : $(FILES_ABS_OBJ)
	@$(call fancyNameArchivingEcho,$@)
	@$(ARCHIVER) $(NAME) $(FILES_ABS_OBJ)

################################################################





$(DIR_OBJ)%.o: $(DIR_SRC)%.cpp
	@$(call fancyNameCompilingEcho,$@)
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

test: all
	$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -o $(EXE) main/copy.cpp $(NAME)
#	$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -o $(EXE) main/mainTextCommands.cpp $(NAME)
#	$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -o $(EXE) main/mainLines.cpp $(NAME)

test_clean:
	rm -f $(EXE)

.PHONY: test test_clean

################################################################
