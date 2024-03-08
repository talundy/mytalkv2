TARGET = mytalk

HEADERS = mytalk_funcs.h client.h server.h

REMOTE = tlundy@unix3.csc.calpoly.edu:~/mytalk

SOURCES = mytalk.c mytalk_funcs.c client.c server.c

OBJECTS = mytalk.o mytalk_funcs.o client.o server.o

FLAGS = -Wall -g -Wextra

PNICO_LIB64 = ~pn-cs357/Given/Talk/lib64 

PNICO_LIB = ~pn-cs357/Given/Talk/lib

PNICO_INCLUDE = ~pn-cs357/Given/Talk/include

all:
	gcc -c $(FLAGS) -I $(PNICO_INCLUDE) $(SOURCES)
	gcc -o mytalk $(FLAGS) $(OBJECTS) -L $(PNICO_LIB64) -L $(PNICO_LIB) -ltalk -lncurses

mytalk:
	make all

clean:
	rm -f *~ *.o mytalk
