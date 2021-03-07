CC = gcc
ARGS = -Wall --std=gnu99 -g -pthread

all: enc_client enc_server dec_client dec_server keygen

enc_client: enc_client.c $(wildcard shared/*.c) $(wildcard shared/*.h)
	${CC} ${ARGS} -o enc_client enc_client.c $(wildcard shared/*.c)

enc_server: enc_server.c $(wildcard shared/*.c) $(wildcard shared/*.h)
	${CC} ${ARGS} -o enc_server enc_server.c $(wildcard shared/*.c)

dec_client: dec_client.c $(wildcard shared/*.c) $(wildcard shared/*.h)
	${CC} ${ARGS} -o dec_client dec_client.c $(wildcard shared/*.c)

dec_server: dec_server.c $(wildcard shared/*.c) $(wildcard shared/*.h)
	${CC} ${ARGS} -o dec_server dec_server.c $(wildcard shared/*.c)

keygen: keygen.c
	${CC} ${ARGS} -o keygen keygen.c

.PHONY: clean format test

clean:
	rm -f enc_client enc_server dec_client dec_server keygen

format:
	clang-format -i $(wildcard shared/*.c) $(wildcard shared/*.h) $(wildcard *.c) --style=Google

.ONESHELL:
test:
	cd test
	bash ./test-script.sh $$RANDOM $$RANDOM
