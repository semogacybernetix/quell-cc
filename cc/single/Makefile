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
prog00=gradnetz
$(prog00):
	make -C ../class $(opfad)vektor.o
	make -C ../../conio $(opfad)vektorcon.o
	make -C ../screen $(opfad)vscr.o
	make -C ../screen $(opfad)jpegscr.o
	make -C ../screen $(opfad)bmpscr.o
	make $(ppfad)$@

$(opfad)$(prog00).o: $(prog00).cc ../class/vektor.h ../../conio/vektorcon.h
	$(comp) $< -c $(copts) -o $@

$(ppfad)$(prog00): $(opfad)$(prog00).o $(opfad)vektorcon.o $(opfad)vektor.o
	$(comp) $(opfad)vektor.o $(opfad)vektorcon.o $(opfad)vscr.o $(opfad)jpegscr.o $(opfad)bmpscr.o -ljpeg $< $(copts) -o $@
#----------------------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------------------
prog08=wavegen
$(prog08):
	make -C ../class $(opfad)vektor.o
	make -C ../../conio/ $(opfad)vektorcon.o
	make $(ppfad)$@

$(opfad)$(prog08).o: $(prog08).cc single.h ../class/vektor.h ../../conio/vektorcon.h
	$(comp) $< -c $(copts2) -o $@

$(ppfad)$(prog08): $(opfad)$(prog08).o $(opfad)single.o $(opfad)vektor.o $(opfad)vektorcon.o
	$(comp) $+ -o $@
#----------------------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------------------
prog04=undos
$(prog04): $(ppfad)$(prog04)
	

$(ppfad)$(prog04): $(prog04).cc
	$(comp) $< $(copts) -o $@
#----------------------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------------------
prog03=tastatur
$(prog03): $(ppfad)$(prog03)
	

$(ppfad)$(prog03): $(prog03).cc
	$(comp) $< $(copts) -lncurses -o $@
#----------------------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------------------
prog01=iftest
$(prog01): $(ppfad)$(prog01)
	

$(opfad)$(prog01).o: $(prog01).cc
	$(comp) $< -c $(copts) -o $@

$(ppfad)$(prog01): $(opfad)$(prog01).o
	$(comp) $+ -o $@
#----------------------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------------------
prog05=planetenberechnung
$(prog05):
	make -C ../class $(opfad)vektor.o
	make -C ../../conio $(opfad)vektorcon.o
	make $(ppfad)$@

$(opfad)$(prog05).o: $(prog05).cc ../class/vektor.h ../../conio/vektorcon.h
	$(comp) $< -c $(copts) -o $@

$(ppfad)$(prog05): $(opfad)$(prog05).o $(opfad)vektor.o $(opfad)vektorcon.o
	$(comp) $+ -o $@
#----------------------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------------------
prog02=fließkomma
$(prog02): $(ppfad)$(prog02)
	

$(ppfad)$(prog02): $(prog02).cc
	$(comp) $< $(copts) -o $@
#----------------------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------------------
prog07=fpubenchmark
$(prog07):
	make -C ../class $(opfad)vektor.o
	make $(ppfad)$@

$(opfad)$(prog07).o: $(prog07).cc single.h ../class/vektor.h ../screen/allscr.h
	$(comp) $< -c $(copts2) -o $@

$(ppfad)$(prog07): $(opfad)$(prog07).o $(opfad)single.o $(opfad)vektor.o $(opfad)libscr.a $(opfad)fbscr.o
	$(comp) $+ -lscr -L$(opfad) -o $@
#----------------------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------------------
prog09=komplextest
$(prog09):
	make -C ../../cc/class $(opfad)vektor.o
	make -C ../../conio $(opfad)vektorcon.o
	make $(ppfad)$@

$(opfad)$(prog09).o: $(prog09).cc ../class/vektor.h ../../conio/vektorcon.h
	$(comp) $< -c $(copts) -o $@

$(ppfad)$(prog09): $(opfad)$(prog09).o $(opfad)vektorcon.o $(opfad)vektor.o
	$(comp) $+ -o $@
#----------------------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------------------
quaternionentest:
	make -C ../class $(opfad)vektor.o
	make -C ../class $(opfad)gruppe.o
	make -C ../../conio $(opfad)vektorcon.o
	make -C ../../conio $(opfad)gruppecon.o
	make $(ppfad)$@

$(opfad)quaternionentest.o: quaternionentest.cc ../class/vektor.h ../../conio/vektorcon.h ../class/gruppe.h ../../conio/gruppecon.h
	$(comp) $< -c $(copts) -o $@

$(ppfad)quaternionentest: $(opfad)vektor.o $(opfad)gruppe.o $(opfad)vektorcon.o $(opfad)gruppecon.o $(opfad)quaternionentest.o
	$(comp) $+ -o $@
#----------------------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------------------
prog06=linearfaktoren
$(prog06):
	make -C ../class $(opfad)vektor.o
	make -C ../../conio $(opfad)vektorcon.o
	make $(ppfad)$@

$(opfad)$(prog06): $(prog06).cc ../class/vektor.h ../../conio/vektorcon.h
	$(comp) $< -c $(copts) -o $@

$(ppfad)$(prog06): $(opfad)$(prog06) $(opfad)vektor.o $(opfad)vektorcon.o
	$(comp) $+ -o $@
#----------------------------------------------------------------------------------------------------------

