CC = g++ -O3 -std=c++11

all: app

spreadsheet.o: spreadsheet.cc spreadsheet.h
	$(CC) spreadsheet.cc -c $(INCS)

main.o: main.cc
	$(CC) main.cc -c $(INCS)

app: main.o spreadsheet.o
	$(CC) main.o spreadsheet.o $(INCS) $(LDLIBS) -o app

clean:
	rm main.o spreadsheet.o app
