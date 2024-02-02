NAME        = file_indexer

CC			= c++
RM			= rm -f
FLAGS		= -Wall -Wextra -Werror -std=c++98 -g

FILES		= main FileIndexer Node BalancedTree 

SRCS		= ${FILES:=.cpp}

OBJS		= ${FILES:=.o}

HEADER		= FileIndexer.hpp Node.hpp BalancedTree.hpp

%.o:		%.cpp ${HEADER}
			${CC} ${FLAGS} -c $< -o $@

${NAME}:	${OBJS} ${HEADER}
			${CC} ${FLAGS} ${OBJS} -o ${NAME} 

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}
		
re:			fclean all

.PHONY:		all clean fclean re