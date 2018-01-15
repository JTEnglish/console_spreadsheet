CC = g++ -O3 -std=c++11

all: app

spreadsheet.o: spreadsheet.cc spreadsheet.h
	$(CC) spreadsheet.cc -c $(INCS)

main.o: main.cc
	$(CC) main.cc -c $(INCS)

app: spreadsheet.o main.o
	$(CC) spreadsheet.o main.o $(INCS) $(LDLIBS) -o app

clean:
	rm *.o app
