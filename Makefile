g10:g10.o dll.o attribute.o attributes.o node.o nodes.o base.o bases.o relation.o relations.o data.o listener.o handler.o
	gcc -ggdb -lpthread -o g10 g10.o dll.o attribute.o attributes.o node.o nodes.o base.o bases.o relation.o relations.o data.o listener.o handler.o

g10.o:g10.c g10.h structs.h
	gcc -ggdb -c g10.c

dll.o:dll.c dll.h
	gcc -ggdb -c dll.c

attribute.o:attribute.c attribute.h
	gcc -ggdb -c attribute.c

attributes.o:attributes.c attributes.h
	gcc -ggdb -c attributes.c

node.o:node.c node.h
	gcc -ggdb -c node.c

nodes.o:nodes.c nodes.h
	gcc -ggdb -c nodes.c

base.o:base.c base.h
	gcc -ggdb -c base.c

bases.o:bases.c bases.h
	gcc -ggdb -c bases.c

relation.o:relation.c relation.h
	gcc -ggdb -c relation.c

relations.o:relations.c relations.h
	gcc -ggdb -c relations.c

data.o:data.c data.h
	gcc -ggdb -c data.c

listener.o:listener.c listener.h
	gcc -ggdb -c listener.c

handler.o:handler.c handler.h
	gcc -ggdb -c handler.c
clean:
	rm *.o
	rm *~
