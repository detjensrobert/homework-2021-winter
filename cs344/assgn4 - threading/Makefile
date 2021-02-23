CC = gcc
ARGS = -Wall --std=gnu99 -g -pthread

OUTFILE = line_processor

$(OUTFILE): $(wildcard *.c) $(wildcard *.h)
	$(CC) $(ARGS) -o $(OUTFILE) $(wildcard *.c)

.PHONY: clean
clean:
	rm -rf $(OUTFILE) $(wildcard vgcore.*)
