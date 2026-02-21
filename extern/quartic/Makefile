# ------------ Makefile mray -------------------------------------------

# --------------------------- Umgebungsvariablen ------------------------------

ifndef PLATFORM
$(error you must set PLATFORM variable (linux))
endif

ifndef CCSTANDARD
$(error you must set CCSTANDARD variable (c++11))
endif

opfad=$(HOME)/bin/$(PLATFORM)/o/
ppfad=$(HOME)/bin/$(PLATFORM)/sbin/

comp=g++

# -------------------------- Makeoptionen ------------------------------------

copts=-std=$(CCSTANDARD) -Wall -Wextra -Wconversion -pedantic-errors -O2

# -------------------------- Ziele -------------------------------------------

allclean:
	rm -f $(opfad)*
	rm -f $(ppfad)*

quartictest:
	make -C ../../cc/class $(opfad)quartic.o
	make -C ../../cc/class $(opfad)vektor.o
	make -C ../../conio $(opfad)vektorcon.o
	make $(ppfad)quartictest

# Abhängigkeitsbaum der h-Dateien voll durchtraversiert
$(opfad)quartictest.o: quartictest.cc ../../cc/class/quartic.h ../../cc/class/vektor.h ../../conio/vektorcon.h
	$(comp) $< -c $(copts) -o $@

$(ppfad)quartictest: $(opfad)quartictest.o $(opfad)quartic.o $(opfad)vektor.o $(opfad)vektorcon.o
	$(comp) $+ -o $@
