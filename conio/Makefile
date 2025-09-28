# ------------ Makefile conio -------------------------------------------

# --------------------------- Umgebung testen  ------------------------------

ifndef PLATFORM
$(error you must set PLATFORM variable (linux))
endif

ifndef CCSTANDARD
$(error you must set CCSTANDARD variable (c++17))
endif

opfad=$(HOME)/bin/$(PLATFORM)/o/
ppfad=$(HOME)/bin/$(PLATFORM)/sbin/

comp=g++
copts=-std=$(CCSTANDARD) -Wall -Wextra -Wconversion -pedantic-errors -O2

# -------------------------- Ziele ------------------------------------------

$(opfad)vektorcon.o: vektorcon.cc vektorcon.h ../cc/class/vektor.h
	$(comp) $< -c $(copts) -o $@

$(opfad)gruppecon.o: gruppecon.cc gruppecon.h vektorcon.h ../cc/class/gruppe.h ../cc/class/vektor.h
	$(comp) $< -c $(copts) -o $@

allclean:
	rm -f $(opfad)*
	rm -f $(ppfad)*

clean:
	rm -f $(opfad)vektorcon.o $(opfad)gruppecon.o

