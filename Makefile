# A simple Makefile
# <Aarshad Mahi and G-00975690>
# CS 262, Lab Section 221
# Lab9

TARGET = automate
PATH = ./out/

CC = gcc
ERROR = -pedantic-errors
CFLAGS = -Og -Wall ${ERROR} -o
OUT = out

all: ${TARGET}.c 
	clear
	${CC} ${CFLAGS} ${TARGET} ${TARGET}.c
clean:
	rm ${TARGET}
	rm -r ./.vscode
run:
	clear
	${CC} ${CFLAGS} ${TARGET} ${TARGET}.c
	${TARGET}
	