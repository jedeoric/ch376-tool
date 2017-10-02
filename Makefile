AS=xa
CC=cl65
CFLAGS=-ttelestrat
LDFILES=../oric-common/lib/ca65/ch376.s


PROGRAM=ch376
SOURCE=src/ch376.c

ASFLAGS=-C -W -e error.txt -l xa_labels.txt -DTARGET_ORIX

$(PROGRAM): $(SOURCE)
	$(CC) $(SOURCE) $(CFLAGS) -o build/usr/bin/$(PROGRAM) $(LDFILES)
