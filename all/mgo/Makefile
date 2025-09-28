# ------------ Makefile mgo -------------------------------------------

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

cgo:
	make -C ../../cc/screen $(opfad)libscr.a
	make -C ../../xwindow/screen $(opfad)xscr.o
	make -C ../../cc/class $(opfad)go.o
	make $(ppfad)cgo

$(ppfad)cgo: $(opfad)cgo.o $(opfad)xgo.o $(opfad)libscr.a $(opfad)xscr.o $(opfad)go.o
	$(comp) $+ $(lopts) -o $@

$(opfad)cgo.o: cgo.cc
	$(comp) $< -c $(copts) -o $@

$(opfad)xgo.o: xgo.cc xgo.h
	$(comp) $< -c $(copts) -o $@

allclean:
	rm -f $(opfad)*
	rm -f $(ppfad)*
