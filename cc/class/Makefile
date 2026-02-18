# ------------ Makefile class -------------------------------------------

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

$(opfad)quartic.o: quartic.cc quartic.h
	$(comp) $< -c $(copts) -o $@

$(opfad)vektor.o: vektor.cc vektor.h
	$(comp) $< -c $(copts) -o $@

$(opfad)gruppe.o: gruppe.cc gruppe.h vektor.h
	$(comp) $< -c $(copts) -o $@

$(opfad)ray.o: ray.cc ray.h ../screen/vscr.h vektor.h
	$(comp) $< -c $(copts) -o $@

$(opfad)game.o: game.cc game.h ray.h ../screen/vscr.h vektor.h ../keyboard/vkbd.h gruppe.h ../../conio/vektorcon.h
	$(comp) $< -c $(copts) -o $@

$(opfad)go.o: go.cc go.h
	$(comp) $< -c $(copts) -o $@

allclean:
	rm -f $(opfad)*
	rm -f $(ppfad)*
