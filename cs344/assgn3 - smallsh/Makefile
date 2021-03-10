CC = gcc
ARGS = -Wall --std=gnu99 -g

OUTFILE = smallsh

smallsh: $(wildcard *.c) $(wildcard *.h)
	$(CC) $(ARGS) -o $(OUTFILE) $(wildcard *.c)

.PHONY: clean test
clean:
	rm -rf $(OUTFILE) junk junk2 $(wildcard vgcore.*) $(wildcard ~/testdir*)

test:
	bash p3testscript.sh
