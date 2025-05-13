CC = gcc
CFLAGS = -I$(IDIR) -g -O0 #voegt directopry $(IDIR) to aan de zoekpaden voor .h files, -g -> debugging, -O0 -> geen compileroptimalisatie
LIBS = -lm #link math bib

IDIR = INCL
ODIR = OBJ
LDIR = LIB
SDIR = SRC


DEPS = $(patsubst %, $(IDIR)/%, *.h)


_SRC = $(wildcard $(SDIR)/*.c) 
_OBJ = $(_SRC:$(SDIR)/%.c=$(ODIR)/%.o)

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
# -c = maak een .o van een .c bestand
# -o = defineerd de naam van het .o bestand
# is afhankelijk van .c file EN van bijhorende .h file!!!!!!!!!!!!!
# DWZ ALS ER GEEN .H FILE VAN DE .C FILE IS DAT HET PROGRAMMA NIET WERKT!!!!!!

BIN/prog1: $(_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


# .PHONY -> als we een file hebben met de naam clean zal dit target nooit runnen
# Daarom zetten we .PHONY ervoor.
.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~core $(INCDIR)/*~



run: BIN/prog1
		./BIN/prog1

pub: BIN/prog1
	cp ~/Desktop/embedded_linux_work/BIN/prog1 /usr/sbin/linuxservice/