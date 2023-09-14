TARGET=uart2udp_2
CROSS=$(CROSS_COMPILE)
CC=$(CROSS)gcc
LD=$(CROSS)ld

INCDIR=

#LIBS=	-lpthread \
#		-ljpeg

LIBDIR=

CFLAGS=  -Wall -Wextra $(INCDIR) $(LIBS) $(LIBDIR)

$(TARGET):$(TARGET).o
	echo $(CC)
	$(CC) $(CFLAGS) $^ -o $@.out



.PHONY:clean
clean:
	-rm -f *.o fv *~ *.out
