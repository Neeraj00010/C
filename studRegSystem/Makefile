########################################################################
####################### Makefile Template ##############################
########################################################################

CC = gcc
CC_FLAGS =  -g -pedantic -W -Wall
FILES = main.c
OUT_EXE = ass2 

build: $(FILES)
	   $(CC) $(CC_FLAGS) -o $(OUT_EXE) $(FILES)

clean: rm -f *.o core *.exe *~

rebuild: clean build