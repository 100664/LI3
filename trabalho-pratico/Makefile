OBJS    = main.o Q2.o Q8.o Q7.o Q9.o aeroporto.o calcularQueries.o flights.o hotel.o parse.o parseFicheiroFlights.o parseFicheiroPassengers.o parseFicheiroReservations.o parseFicheiroUsers.o Q1.o Q3.o Q4.o Q5.o Q6.o reservations.o users.o utils.o writeOutput.o menu.o
OBJST    = teste.o Q2.o Q8.o Q7.o Q9.o aeroporto.o calcularQueries.o flights.o hotel.o parse.o parseFicheiroFlights.o parseFicheiroPassengers.o parseFicheiroReservations.o parseFicheiroUsers.o Q1.o Q3.o Q4.o Q5.o Q6.o reservations.o users.o utils.o writeOutput.o
SOURCE  = src/main.c src/Q8.c src/Q7.c src/Q2.c src/Q9.c src/teste.c src/aeroporto.c src/calcularQueries.c src/flights.c src/hotel.c src/parse.c src/parseFicheiroFlights.c src/parseFicheiroPassengers.c src/parseFicheiroReservations.c src/parseFicheiroUsers.c src/Q1.c src/Q3.c src/Q4.c src/Q5.c src/Q6.c src/reservations.c src/users.c src/utils.c src/writeOutput.c
HEADER  = Includes/aeroporto.c Includes/Q7.h Includes/Q2.h Includes/Q9.h Includes/Q8.H  Includes/calcularQueries.c Includes/flights.c Includes/hotel.c Includes/parse.c Includes/parseFicheiroFlights.c Includes/parseFicheiroPassengers.c Includes/parseFicheiroReservations.c Includes/parseFicheiroUsers.c Includes/Q1.c Includes/Q3.c Includes/Q4.c Includes/Q5.c Includes/Q6.c Includes/reservations.c Includes/users.c Includes/utils.c Includes/writeOutput.c
OUT     = programa-principal
TESTES_OUT = programa-testes
CC      = gcc
GLIBCFAGS := `pkg-config --cflags glib-2.0`
FLAGS      =  $(GLIBCFAGS) -g -Wall
LFLAGS    := `pkg-config --libs glib-2.0` -lcurses -O3 -lm

all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LFLAGS) -o $(OUT) 

# objs:
# 	$(CC) $(FLAGS) -c src/*.c -std=gnu17

all: programa-principal programa-testes

programa-principal: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LFLAGS) -o $(OUT)

programa-testes: teste.o
	$(CC) $(FLAGS) $(OBJST) $(LFLAGS) -o $(TESTES_OUT)

teste.o: src/teste.c
	$(CC) $(FLAGS) -c src/teste.c -std=gnu17

main.o: src/main.c 

	$(CC) $(FLAGS) -c src/main.c -std=gnu17

parse.o: src/parse.c 

	$(CC) $(FLAGS) -c src/parse.c -std=gnu17

Q1.o: src/Q1.c

	$(CC) $(FLAGS) -c src/Q1.c -std=gnu17	

Q2.o: src/Q2.c

	$(CC) $(FLAGS) -c src/Q2.c -std=gnu17	
Q7.o: src/Q7.c

	$(CC) $(FLAGS) -c src/Q7.c -std=gnu17	

Q8.o: src/Q8.c

	$(CC) $(FLAGS) -c src/Q8.c -std=gnu17	

Q3.o: src/Q3.c

	$(CC) $(FLAGS) -c src/Q3.c -std=gnu17	

Q4.o: src/Q4.c

	$(CC) $(FLAGS) -c src/Q4.c -std=gnu17

Q5.o: src/Q5.c
	$(CC) $(FLAGS) -c src/Q5.c -std=gnu17

Q6.o: src/Q6.c
	$(CC) $(FLAGS) -c src/Q6.c -std=gnu17
Q9.o: src/Q9.c
	$(CC) $(FLAGS) -c src/Q9.c -std=gnu17

utils.o: src/utils.c
	$(CC) $(FLAGS) -c src/utils.c -std=gnu17

writeOutput.o: src/writeOutput.c

	$(CC) $(FLAGS) -c src/writeOutput.c -std=gnu17

users.o: src/users.c

	$(CC) $(FLAGS) -c src/users.c -std=gnu17	

reservations.o: src/reservations.c

	$(CC) $(FLAGS) -c src/reservations.c -std=gnu17

parseFicheiroFlights.o: src/parseFicheiroFlights.c

	$(CC) $(FLAGS) -c src/parseFicheiroFlights.c -std=gnu17	

parseFicheiroPassengers.o: src/parseFicheiroPassengers.c

	$(CC) $(FLAGS) -c src/parseFicheiroPassengers.c -std=gnu17	

parseFicheiroReservations.o: src/parseFicheiroReservations.c

	$(CC) $(FLAGS) -c src/parseFicheiroReservations.c -std=gnu17	

parseFicheiroUsers.o: src/parseFicheiroUsers.c

	$(CC) $(FLAGS) -c src/parseFicheiroUsers.c -std=gnu17		

hotel.o: src/hotel.c

	$(CC) $(FLAGS) -c src/hotel.c -std=gnu17

aeroporto.o: src/aeroporto.c

	$(CC) $(FLAGS) -c src/aeroporto.c -std=gnu17

calcularQueries.o: src/calcularQueries.c

	$(CC) $(FLAGS) -c src/calcularQueries.c -std=gnu17

flights.o: src/flights.c

	$(CC) $(FLAGS) -c src/flights.c -std=gnu17

menu.o: src/menu.c

	$(CC) $(FLAGS) -c src/menu.c -std=gnu17


clean:
	rm -f $(OBJS) $(OBJST) $(OUT) $(TESTES_OUT)
