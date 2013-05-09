NAME		=	UDF_reader

CXX			=	g++
RM			=	rm
CXXFLAGS	=	-W -Wall -std=c++0x -ggdb3
SOURCES		=	main.cpp		\
	AVDP.cpp	\
	PrimaryVDesc.cpp	\
	Tag.cpp	\
	VStructDesc.cpp	\
	UDF.cpp \
	PartitionDescriptor.cpp \
	LogicalVolumeDescriptor.cpp

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

