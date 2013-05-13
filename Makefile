NAME		=	UDF_reader

CXX			=	g++
RM			=	rm
CXXFLAGS	=	-W -Wall -std=c++0x -DNDEBUG #-ggdb3
SOURCES		=	main.cpp		\
	AVDP.cpp	\
	PrimaryVDesc.cpp	\
	Tag.cpp	\
	VStructDesc.cpp	\
	UDF.cpp \
	PartitionDescriptor.cpp \
	DString.cpp \
	LogicalVolumeDescriptor.cpp  \
	Descriptor.cpp \
	UnallocSpaceDesc.cpp \
	FileSystem.cpp \
	FileSetDesc.cpp \
	CommandCD.cpp \
	CommandCP.cpp \
	CommandDIR.cpp \
	CommandEXIT.cpp \
	CommandFDISK.cpp \
	CommandParser.cpp \
	FileSystemTree.cpp \
	Node.cpp \
	NodeInformation.cpp \
	ParseLinkCD.cpp \
	ParseLinkCP.cpp \
	ParseLinkDIR.cpp \
	ParseLinkEXIT.cpp \
	ParseLinkFDISK.cpp \
	Prompt.cpp	\
	ICBTag.cpp \
	FileEntry.cpp

OBJS		=	$(SOURCES:.cpp=.o)


.PHONY:	all clean fclean re


$(NAME):	$(OBJS)
	$(CXX) -o $(NAME) $(OBJS) $(LDFLAGS)

all: 	$(NAME)

clean:
	$(RM) -f $(OBJS)
	$(RM) -f *~

fclean:	clean
	$(RM) -f $(NAME)

re:	fclean all

