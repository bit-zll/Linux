BIN=out
CFLAGS=-g
$(BIN):test.c a.c b.c d.c
	gcc $^ -o $@ $(CFLAGS)

clean:
	rm $(BIN)


#out:test.c a.c b.c d.c
#	gcc $^ -o $@



#out:test.o
#	gcc test.o -o out
#test.o:test.c
#	gcc -c test.c -o test.o











#all:test out
#test:test.c
#	gcc test.c -o test
#
#out:test.c
#	gcc test.c -o out
