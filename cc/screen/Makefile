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
    vscr\
    memscr\
    bmpscr\
    jpegscr\
    psscr\

pmods= $(addprefix $(opfad), $(mods))
pobjs= $(addsuffix .o, $(pmods))

# -------------------------- Ziele ------------------------------------------

allclean:
	rm -f $(opfad)*
	rm -f $(ppfad)*

clean:
	rm -f $(opfad)libscr.a
	rm -f $(pobjs)
	rm -f $(opfad)jpeg.o
	rm -f $(opfad)leedct.o

libscr: $(opfad)libscr.a
	

$(opfad)libscr.a: $(pobjs)
	ar rs $@ $(pobjs)
	rm -f $(pobjs)

$(opfad)vscr.o: vscr.cc vscr.h ../class/vektor.h
	$(comp) $< -c $(copts) -o $@

$(opfad)memscr.o: memscr.cc memscr.h vscr.h ../class/vektor.h
	$(comp) $< -c $(copts) -o $@

$(opfad)bmpscr.o: bmpscr.cc bmpscr.h vscr.h ../class/vektor.h
	$(comp) $< -c $(copts) -o $@

$(opfad)psscr.o: psscr.cc psscr.h vscr.h ../class/vektor.h
	$(comp) $< -c $(copts) -o $@

$(opfad)jpegscr.o: jpegscr.cc jpegscr.h vscr.h ../class/vektor.h
	$(comp) $< -c $(copts2) -o $@
