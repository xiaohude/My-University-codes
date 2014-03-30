main:main.o sql.o staffedit.o billedit.o dishesedit.o dishededit.o tableinfoedit.o
	gcc main.o sql.o staffedit.o billedit.o dishesedit.o dishededit.o tableinfoedit.o -o main -lpthread -L /usr/lib/mysql -lmysqlclient
sql.o:sql.c sql.h
	gcc -c sql.c 
staffedit.o:	
	gcc -c staffedit.c
billedit.o:
	gcc -c billedit.c
dishesedit.o:
	gcc -c dishesedit.c
dishededit.o:
	gcc -c dishededit.c
tableinfoedit.o:
	gcc -c tableinfoedit.c
main.o:main.c
	gcc -c main.c
clean:
	rm -f *.o main
