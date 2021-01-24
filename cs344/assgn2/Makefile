CC = gcc
ARGS = -Wall --std=gnu99 -g

movies_by_year: main.c select.c movies.c process.c
	$(CC) $(ARGS) -o movies_by_year main.c select.c movies.c process.c

clean:
	rm -rf $(wildcard detjensr.movies.*) $(wildcard vgcore.*) movies_by_year
