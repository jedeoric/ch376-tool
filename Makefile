AS=xa
CC=cl65
CFLAGS=-ttelestrat
LDFILES=../telemon/src/include/libs/ca65/ch376.s


PROGRAM=ch376
SOURCE=src/ch376.c

ASFLAGS=-C -W -e error.txt -l xa_labels.txt -DTARGET_ORIX

$(PROGRAM): $(SOURCE)
	$(CC) $(SOURCE) $(CFLAGS) -o $(PROGRAM) $(LDFILES)

test:
	mkdir -p build/usr/bin/
	mkdir -p build/usr/share/man
	mkdir -p build/usr/share/ipkg  
	cp $(PROGRAM) build/usr/bin/
	cp src/man/$(PROGRAM).hlp build/usr/share/man
	cp src/ipkg/$(PROGRAM).csv build/usr/share/ipkg
	echo nothing