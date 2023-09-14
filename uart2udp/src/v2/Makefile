TARGET=uart2udp_2
CROSS=
CC=$(CROSS)gcc
LD=$(CROSS)ld

INCDIR=

#LIBS=	-lpthread \
#		-ljpeg

LIBDIR=

CFLAGS=  -Wall -Wextra $(INCDIR) $(LIBS) $(LIBDIR)

$(TARGET):$(TARGET).o
	$(CC) $(CFLAGS) $^ -o $@.out



.PHONY:clean
clean:
	-rm -f *.o fv *~ *.out
