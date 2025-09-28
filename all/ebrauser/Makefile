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

#copts=-std=$(CCSTANDARD) -Wall -Wextra -Wconversion -pedantic-errors -O2
# noch zu viele Conversion Warnungen bei xegenerator und xebrauser
copts=-std=$(CCSTANDARD) -Wall -Wextra -pedantic-errors -O2
lopts=-L$(opfad) -lquadmath -lscr -lpthread -ljpeg -lX11

# -------------------------- Ziele ------------------------------------------

xegenerator:
	make $(ppfad)xegenerator

$(ppfad)xegenerator: $(opfad)xegenerator.o
	$(comp) $+ -lpthread -o $@

$(opfad)xegenerator.o: xegenerator.cc
	$(comp) $< -c $(copts) -o $@

xebrauser:
	make -C ../../cc/class/ $(opfad)vektor.o
	make -C ../../cc/keyboard $(opfad)vkbd.o
	make -C ../../xwindow/keyboard $(opfad)xkbd.o
	make -C ../../cc/screen $(opfad)libscr.a
	make -C ../../xwindow/screen $(opfad)xscr.o
	make $(ppfad)xebrauser

$(ppfad)xebrauser: $(opfad)xebrauser.o $(opfad)vektor.o $(opfad)vkbd.o $(opfad)xkbd.o $(opfad)libscr.a $(opfad)xscr.o
	$(comp) $+ $(lopts) -o $@

$(opfad)xebrauser.o: xebrauser.cc
	$(comp) $< -c $(copts) -o $@

allclean:
	rm -f $(opfad)*
	rm -f $(ppfad)*

