a.out: client_list.o list.o list_iterator.o iterator.o algorithms.o
	gcc client_list.o list.o list_iterator.o iterator.o algorithms.o

client_list.o: client_list.c list_iterator.h algorithms.h list.h
	gcc -c -w client_list.c
list.o: list.c list.h
	gcc -c -w list.c
list_iterator.o: list_iterator.c list_iterator.h list.h
	gcc -c -w list_iterator.c
iterator.o:	iterator.c iterator.h
	gcc -c -w iterator.c
algorithms.o: algorithms.c algorithms.h
	gcc -c -w algorithms.c