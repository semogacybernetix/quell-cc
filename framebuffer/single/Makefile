# ------------ Makefile framebuffer/single -------------------------------------------

ifndef PLATFORM
$(PLATFORM not set)
endif

ifndef CCSTANDARD
$(error you must set CCSTANDARD variable (c++11))
endif

ppfad=$(HOME)/bin/$(PLATFORM)/sbin/
opfad=$(HOME)/bin/$(PLATFORM)/o/

comp=g++
#copts=-std=$(CCSTANDARD) -Wall -Wextra -Wconversion -pedantic-errors -O2
copts=-std=$(CCSTANDARD) -Wall -Wextra -pedantic-errors -O2
scropts=-L/root/bin/linux/o -lscr
xopts=-L/usr/X11R6/lib -lX11
jpgopts=-ljpeg

# ---------------------------------------- Unteraufrufe ---------------------------------------------------
allclean:
	rm -f $(opfad)*
	rm -f $(ppfad)*

# ------------------------------------------ Programme ----------------------------------------------------

#----------------------------------------------------------------------------------------------------------
fbneu:
	make $(ppfad)$@

$(ppfad)fbneu: fbneu.cc
	$(comp) $< $(copts) -o $@

#----------------------------------------------------------------------------------------------------------
timings:
	make $(ppfad)$@

$(ppfad)timings: timings.cc
	$(comp) $< $(copts) -o $@

#----------------------------------------------------------------------------------------------------------
fbquad:
	make -C ../../cc/class $(opfad)vektor.o
	make -C ../../cc/screen/ $(opfad)vscr.o
	make -C ../screen/ $(opfad)fbscr.o
	make $(ppfad)$@

$(ppfad)fbquad: $(opfad)fbquad.o $(opfad)fbscr.o $(opfad)vscr.o $(opfad)vektor.o
	$(comp) $(opfad)fbquad.o $(opfad)fbscr.o $(opfad)vscr.o $(opfad)vektor.o -o $@

$(opfad)fbquad.o: fbquad.cc ../screen/fbscr.h ../../cc/screen/vscr.h ../../cc/class/vektor.h
	$(comp) $< -c $(copts) -o $@

#----------------------------------------------------------------------------------------------------------
apfel:
	make -C ../../cc/class $(opfad)vektor.o
	make -C ../../conio $(opfad)vektorcon.o
	make -C ../../cc/screen/ $(opfad)vscr.o
	make -C ../../cc/screen/ $(opfad)memscr.o
	make -C ../../cc/screen/ $(opfad)bmpscr.o
	make -C ../screen/ $(opfad)fbscr.o
	make $(ppfad)$@

$(ppfad)apfel: $(opfad)apfel.o $(opfad)fbscr.o $(opfad)xscr.o $(opfad)memscr.o $(opfad)bmpscr.o $(opfad)vscr.o $(opfad)vektorcon.o $(opfad)vektor.o
	$(comp) $(opfad)apfel.o $(opfad)fbscr.o $(opfad)xscr.o $(opfad)memscr.o $(opfad)bmpscr.o $(opfad)vscr.o $(opfad)vektorcon.o $(opfad)vektor.o -lX11 -o $@

$(opfad)apfel.o: apfel.cc ../../cc/screen/allscr.h ../../cc/screen/memscr.h ../../cc/screen/bmpscr.h ../screen/fbscr.h ../../cc/screen/vscr.h ../../conio/vektorcon.h ../../cc/class/vektor.h
	$(comp) $< -c $(copts) -o $@
#----------------------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------------------
jpegview:
	make -C ../../cc/class $(opfad)vektor.o
	make -C ../../cc/screen/ $(opfad)vscr.o
	make -C ../../cc/screen/ $(opfad)jpegscr.o
	make -C ../screen/ $(opfad)fbscr.o
	make $(ppfad)$@

$(ppfad)jpegview: $(opfad)jpegview.o $(opfad)fbscr.o $(opfad)vscr.o $(opfad)vektor.o
	$(comp) $(opfad)jpegview.o $(opfad)fbscr.o $(opfad)jpegscr.o $(opfad)vscr.o $(opfad)vektor.o -ljpeg -o $@

$(opfad)jpegview.o: jpegview.cc
	$(comp) $< -c $(copts) -o $@
#----------------------------------------------------------------------------------------------------------

