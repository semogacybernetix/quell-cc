# ------------ Makefile screen -------------------------------------------

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

# -------------------------- Make Optionen  ------------------------------------

copts=-std=$(CCSTANDARD) -Wall -Wextra -Wconversion -pedantic-errors -O2
copts2=-std=$(CCSTANDARD) -Wall -Wextra -pedantic-errors -O2

mods=\
    xscr\

pmods= $(addprefix $(opfad), $(mods))
pobjs= $(addsuffix .o, $(pmods))

# -------------------------- Ziele ------------------------------------------

allclean:
	rm -f $(opfad)*
	rm -f $(ppfad)*

clean:
	rm -f $(pobjs)

$(opfad)xscr.o: xscr.cc xscr.h ../../cc/screen/vscr.h ../../cc/class/vektor.h
	$(comp) $< -c $(copts) -o $@

