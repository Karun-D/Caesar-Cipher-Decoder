CC = gcc
CFLAGS = -Wall -std=c11 -Iinclude

# Add the other questions to this command as you go
all: Q1 Q2 Q3

# Compile this for Question #1
Q1: Q1.o frequency_table.o
	$(CC) $(CFLAGS) -o frequency_table frequency_table.o Q1.o

frequency_table.o: frequency_table.c
	$(CC) $(CFLAGS) -c frequency_table.c -o frequency_table.o

Q1.o: Q1.c
	$(CC) $(CFLAGS) -c Q1.c -o Q1.o

# Compile this for Question #2
Q2: Q2.o decode.o
	$(CC) $(CFLAGS) -o decode decode.o Q2.o

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c -o decode.o

Q2.o: Q2.c
	$(CC) $(CFLAGS) -c Q2.c -o Q2.o

# Compile this for Question #3
Q3: Q3.o Q2.o copyrecords.o
	$(CC) $(CFLAGS) -o copyrecords copyrecords.o Q3.o Q2.o

copyrecords.o: copyrecords.c
	$(CC) $(CFLAGS) -c copyrecords.c -o copyrecords.o

Q3.o: Q3.c
	$(CC) $(CFLAGS) -c Q3.c -o Q3.o


clean:
	rm *.o frequency_table decode copyrecords