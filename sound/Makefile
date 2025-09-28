# ------------ Makefile ebrauser -------------------------------------------

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
lopts=-L$(opfad) -lscr -lpthread -ljpeg -lX11

# -------------------------- Ziele ------------------------------------------

sound:
	make $(ppfad)sound

$(ppfad)sound: $(opfad)sound.o
	$(comp) $+ -o $@

$(opfad)sound.o: sound.cc
	$(comp) $< -c $(copts) -o $@

allclean:
	rm -f $(opfad)*
	rm -f $(ppfad)*

