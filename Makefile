g10:g10.o dll.o attribute.o attributes.o node.o nodes.o base.o bases.o relation.o relations.o data.o listener.o handler.o output.o parser.o config.o writer.o reader.o logging.o
	gcc -ggdb -lpthread -o g10 g10.o dll.o attribute.o attributes.o node.o nodes.o base.o bases.o relation.o relations.o data.o listener.o handler.o output.o parser.o config.o writer.o reader.o logging.o

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

output.o:output.c output.h
	gcc -ggdb -c output.c

parser.o:parser.c parser.h
	gcc -ggdb -c parser.c

config.o:config.c config.h
	gcc -ggdb -c config.c

writer.o:writer.c writer.h
	gcc -ggdb -c writer.c

reader.o:reader.c reader.h
	gcc -ggdb -c reader.c

logging.o:logging.c logging.h
	gcc -ggdb -c logging.c

clean:
	rm *.o
	rm *~

data:
	rm base.g10
	rm base_attribute.g10
	rm node.g10
	rm node_attribute.g10
