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

allclean:
	rm -f $(opfad)*
	rm -f $(ppfad)*

$(opfad)fbscr.o: fbscr.cc fbscr.h ../../cc/screen/vscr.h ../../cc/class/vektor.h
	$(comp) $< -c $(copts) -o $@


