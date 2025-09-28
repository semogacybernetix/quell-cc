# ------------ Makefile single -----------------------------------------------------

#-------------- Umgebung testen ----------------------------------------------------

ifndef PLATFORM
$(PLATFORM Variable (linux) ist nicht gesetzt)
endif

ifndef CCSTANDARD
$(CC-Standard Variable (c++17) ist nicht gesetzt)
endif

opfad=$(HOME)/bin/$(PLATFORM)/o/
ppfad=$(HOME)/bin/$(PLATFORM)/sbin/

comp=g++

# -------------------------- Make Optionen  ------------------------------------

copts=-std=$(CCSTANDARD) -Wall -Wextra -Wconversion -pedantic-errors -O2
copts2=-std=$(CCSTANDARD) -Wall -Wextra -pedantic-errors -O2
scropts=-L$(opfad) -lscr
xopts=-L/usr/X11R6/lib -lX11
jpgopts=-ljpeg
lopts=-L$(opfad) -lscr -ljpeg -lX11

#--------------------------- Unteraufrufe -----------------------------------------------------------------
allclean:
	rm -f $(opfad)*
	rm -f $(ppfad)*

$(opfad)single.o: single.cc single.h ../class/vektor.h
	$(comp) $< -c $(copts) -o $@

#-------------------------- Programme ---------------------------------------------------------------------

#----------------------------------------------------------------------------------------------------------
fließkomma: $(ppfad)fließkomma
	

$(ppfad)fließkomma: fließkomma.cc
	$(comp) $< $(copts) -o $@
#----------------------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------------------
fpubenchmark: $(ppfad)fpubenchmark
	

$(ppfad)fpubenchmark: $(opfad)fpubenchmark.o $(opfad)single.o $(opfad)vektor.o $(opfad)libscr.a $(opfad)fbscr.o
	$(comp) $(opfad)fpubenchmark.o $(opfad)single.o $(opfad)vektor.o $(opfad)fbscr.o -lscr -L$(opfad) -o $@

$(opfad)fpubenchmark.o: fpubenchmark.cc single.h ../class/vektor.h ../screen/allscr.h
	$(comp) $< -c $(copts2) -o $@
#----------------------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------------------
wavegen:
	make -C ../../cc/class $(opfad)vektor.o
	make $(ppfad)$@

$(opfad)wavegen.o: wavegen.cc single.h ../class/vektor.h
	$(comp) $< -c $(copts2) -o $@

$(ppfad)wavegen: $(opfad)wavegen.o $(opfad)single.o $(opfad)vektor.o
	$(comp) $(opfad)wavegen.o $(opfad)single.o $(opfad)vektor.o -o $@
#----------------------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------------------
komplextest:
	make -C ../../cc/class $(opfad)vektor.o
	make -C ../../conio $(opfad)vektorcon.o
	make $(ppfad)$@

$(opfad)komplextest.o: komplextest.cc ../class/vektor.h
	$(comp) $< -c $(copts) -o $@

$(ppfad)komplextest: $(opfad)komplextest.o $(opfad)vektorcon.o $(opfad)vektor.o
	$(comp) $(opfad)komplextest.o $(opfad)vektorcon.o $(opfad)vektor.o -o $@

#----------------------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------------------
linearfaktoren:
	make -C ../../cc/class $(opfad)vektor.o
	make -C ../../conio $(opfad)vektorcon.o
	make $(ppfad)$@

$(opfad)linearfaktoren.o: linearfaktoren.cc ../../conio/vektorcon.h ../class/vektor.h
	$(comp) $< -c $(copts) -o $@

$(ppfad)linearfaktoren: $(opfad)linearfaktoren.o $(opfad)vektorcon.o $(opfad)vektor.o
	$(comp) $(opfad)linearfaktoren.o $(opfad)vektorcon.o $(opfad)vektor.o -o $@

#----------------------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------------------
quaternionentest:
	make -C ../../cc/class $(opfad)vektor.o
	make -C ../../cc/class $(opfad)gruppe.o
	make -C ../../conio $(opfad)vektorcon.o
	make -C ../../conio $(opfad)gruppecon.o
	make $(ppfad)$@

$(opfad)quaternionentest.o: quaternionentest.cc
	$(comp) $< -c $(copts) -o $@

$(ppfad)quaternionentest: $(opfad)vektor.o $(opfad)gruppe.o $(opfad)vektorcon.o $(opfad)gruppecon.o $(opfad)quaternionentest.o
	$(comp) $(opfad)vektor.o $(opfad)gruppe.o $(opfad)vektorcon.o $(opfad)gruppecon.o $(opfad)quaternionentest.o -o $@

#----------------------------------------------------------------------------------------------------------
