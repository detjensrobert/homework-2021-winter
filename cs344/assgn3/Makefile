CC = gcc
ARGS = -Wall --std=gnu99 -g

OUTFILE = smallsh

smallsh: $(wildcard *.c)
	$(CC) $(ARGS) -o $(OUTFILE) $(wildcard *.c)

clean:
	rm -rf $(OUTFILE) junk junk2 $(wildcard vgcore.*)
