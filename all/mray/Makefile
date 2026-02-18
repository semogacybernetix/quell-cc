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
lopts=-lpthread -ljpeg -lX11 -lncurses
#lopts=-L$(opfad) -lscr -lpthread -ljpeg -lX11
#lopts=-L$(opfad) -lquadmath -lscr -lpthread -ljpeg -lX11

# -------------------------- Ziele -------------------------------------------

allclean:
	rm -f $(opfad)*
	rm -f $(ppfad)*

xray:
	make -C ../../cc/class $(opfad)quartic.o
	make -C ../../cc/class $(opfad)vektor.o
	make -C ../../cc/class $(opfad)gruppe.o
	make -C ../../cc/class $(opfad)ray.o
	make -C ../../cc/class $(opfad)game.o

	make -C ../../conio/ $(opfad)vektorcon.o

	make -C ../../cc/keyboard $(opfad)vkbd.o
	make -C ../../xwindow/keyboard $(opfad)xkbd.o
	make -C ../../framebuffer/keyboard $(opfad)nckbd.o

	make -C ../../cc/screen $(opfad)vscr.o
	make -C ../../xwindow/screen $(opfad)xscr.o
	make -C ../../framebuffer/screen $(opfad)fbscr.o
	make -C ../../cc/screen/ $(opfad)jpegscr.o
	make -C ../../cc/screen/ $(opfad)bmpscr.o

	make $(ppfad)xray

# Abhängigkeitsbaum der h-Dateien voll durchtraversiert
$(opfad)xray.o: xray.cc ../../cc/class/game.h ../../cc/class/ray.h ../../cc/class/quartic.h ../../cc/class/vektor.h ../../cc/screen/vscr.h ../../cc/keyboard/vkbd.h ../../cc/screen/allscr.h ../../xwindow/keyboard/xkbd.h ../../framebuffer/keyboard/nckbd.h ../../cc/screen/memscr.h ../../cc/screen/bmpscr.h ../../cc/screen/jpegscr.h ../../cc/screen/psscr.h ../../framebuffer/screen/fbscr.h ../../xwindow/screen/xscr.h
	$(comp) $< -c $(copts) -o $@

$(ppfad)xray: $(opfad)quartic.o $(opfad)vektor.o $(opfad)gruppe.o $(opfad)ray.o $(opfad)game.o $(opfad)vektorcon.o $(opfad)vkbd.o $(opfad)xkbd.o $(opfad)nckbd.o $(opfad)vscr.o $(opfad)xscr.o $(opfad)fbscr.o $(opfad)jpegscr.o $(opfad)bmpscr.o $(opfad)xray.o
	$(comp) $+ $(lopts) -o $@

symmetriegruppen:
	make -C ../../cc/class $(opfad)vektor.o
	make -C ../../cc/class $(opfad)gruppe.o
	make -C ../../cc/class $(opfad)ray.o
	make -C ../../cc/class $(opfad)game.o

	make -C ../../conio $(opfad)vektorcon.o
	make -C ../../conio $(opfad)gruppecon.o

	make -C ../../cc/keyboard $(opfad)vkbd.o
	make -C ../../xwindow/keyboard $(opfad)xkbd.o

	make -C ../../cc/screen $(opfad)vscr.o
	make -C ../../xwindow/screen $(opfad)xscr.o

	make $(ppfad)symmetriegruppen

# Abhängigkeitsbaum der h-Dateien noch nicht durchtraversiert
$(opfad)symmetriegruppen.o: symmetriegruppen.cc ../../cc/class/game.h ../../cc/class/ray.h ../../cc/screen/vscr.h ../../cc/keyboard/vkbd.h ../../cc/screen/allscr.h ../../xwindow/keyboard/xkbd.h
	$(comp) $< -c $(copts) -o $@

$(ppfad)symmetriegruppen: $(opfad)vektor.o $(opfad)gruppe.o $(opfad)ray.o $(opfad)game.o $(opfad)vektorcon.o $(opfad)gruppecon.o $(opfad)vkbd.o $(opfad)xkbd.o $(opfad)vscr.o $(opfad)xscr.o $(opfad)symmetriegruppen.o
	$(comp) $+ $(lopts) -o $@

