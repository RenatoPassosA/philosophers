NAME = philo
CC = cc
CCFLAGS = -Wall -Wextra -Werror -g -ggdb
SRC = main.o check_args.o getters_and_setters.o routine.o start_data.o start_dinner.o monitor.o utils.o



#NUMBERS					=	1 800 200 200   # The philosopher should not eat and should die - OK
#NUMBERS					=	5 800 200 200   # No philosopher should die. - OK
#NUMBERS					=	5 900 200 200 7 # No philosopher should die. - OK
#NUMBERS					=	4 410 200 200   # No philosopher should die. - OK
#NUMBERS					=	4 310 200 100 7 # One philosopher should die. - OK

#NUMBERS					=	4 10 200 100	#One philosopher should die - OK

#NUMBERS					=	5 410 200 100 7 # One philosopher should die. - OK
#NUMBERS					=	5 120 80 80 	# Moana tolds all will die - OK
#NUMBERS					=	2 200 50 50 1 #- OK
#NUMBERS					=	50 1000 60 60 1 #- OK
#NUMBERS					=	2 110 50 50 2 #- OK

#NUMBERS					=	4 200 205 200	# One should die - OK
#NUMBERS					=	4 410 200 200 10	# No one should die. Stop after 10 - ok
#NUMBERS					=	-5 600 200 200	# ERROR - CRASH - OK
#NUMBERS					=	5 -5 200 200	# ERROR - CRASH - OK
#NUMBERS					=	4 600 -5 200	# ERROR - CRASH - OK
#NUMBERS					=	5 600 200 -5	# ERROR - CRASH - OK
#NUMBERS					=	4 600 200 200 -5	# ERROR - CRASH - OK
#NUMBERS					=	5 600 150 150	# No one should die - OK
#NUMBERS					=	4 410 200 200	# No one should die - OK
#NUMBERS					=	100 800 200 200	# No one should die - OK
#NUMBERS					=	105 800 200 200	# No one should die - OK

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CCFLAGS) -o $(NAME) $(SRC) -g

.o:.c
	$(CC) $(CCFLAGS) -c $< -o $@ -lpthread

clean:
	rm -f $(SRC)

fclean: clean
	rm -f $(NAME)

re: clean all

run: re
	./$(NAME) $(NUMBERS)

compile:
	$(CC) main.c check_args.c getters_and_setters.c routine.c start_data.c start_dinner.c monitor.c utils.c -o $(NAME) -g -O0 -pthread

.PHONY: all bonus clean fclean

#valgrind --tool=helgrind -s ./philosophers 4 410 200 200 10