# ------------ Makefile xwindow/single -------------------------------------------

# Erst die cc-Datei, dann die copts, dann die o-Dateien, dann der o-Name, dann die libflags
# cc-Datei ganz am Ende: Fehler aber teilweise gehts
# -Libflags vor o-Namen und o-Dateien: Fehler aber teilweise gehts
# hat 4 Stunden gedauert, das rauszukriegen

ifndef PLATFORM
$(error you must set PLATFORM variable (linux))
endif

ifndef CCSTANDARD
$(error you must set CCSTANDARD variable (c++11))
endif

ppfad=$(HOME)/bin/$(PLATFORM)/sbin/
opfad=$(HOME)/bin/$(PLATFORM)/o/

comp=g++
copts=-std=$(CCSTANDARD) -Wall -Wextra -Wconversion -pedantic-errors -O2
scropts=-L/root/bin/linux/o -lscr
xopts=-L/usr/X11R6/lib -lX11
jpgopts=-ljpeg

# -------------------------- Unteraufrufe ------------------------------------------

$(opfad)vektor.o:
	make -C ../../cc/class $@

$(opfad)libscr.a:
	make -C ../../cc/screen $@

$(opfad)xscr.o:
	make -C ../../xwindow/screen $@

$(opfad)vkbd.o:
	make -C ../../cc/keyboard $@

$(opfad)xkbd.o:
	make -C ../../xwindow/keyboard $@

$(opfad)cpicture.o:
	make -C ../../cc/class $@

$(opfad)cxpicture.o:
	make -C ../../xwindow/class $@

allclean:
	rm -f $(opfad)*
	rm -f $(ppfad)*

# -------------------------- Programme ------------------------------------------

bmpdoubl: bmpdoubl.cc $(opfad)libscr.a $(opfad)xscr.o $(opfad)vkbd.o $(opfad)xkbd.o
	$(comp) $< $(copts) $(opfad)xscr.o $(opfad)vkbd.o $(opfad)xkbd.o $(scropts) $(xopts) $(jpgopts) -o $(ppfad)$@

deinterlace: deinterlace.cc $(opfad)libscr.a
	$(comp) $< $(copts) $(scropts) -o $(ppfad)$@

example: example.cc
	$(comp) $< $(copts) $(xopts) $(jpgopts) -o $(ppfad)$@

jpgdoubl: jpgdoubl.cc $(opfad)libscr.a $(opfad)xscr.o $(opfad)vkbd.o $(opfad)xkbd.o
	$(comp) $< $(copts) $(opfad)xscr.o $(scropts) $(opfad)vkbd.o $(opfad)xkbd.o $(xopts) $(jpgopts) -o $(ppfad)$@

kubspl: kubspl.cc $(opfad)libscr.a $(opfad)xscr.o
	$(comp) $< $(copts) $(opfad)xscr.o $(scropts) $(xopts) -o $(ppfad)$@

quadspl: quadspl.cc $(opfad)libscr.a $(opfad)xscr.o
	$(comp) $< $(copts) $(opfad)xscr.o $(scropts) $(xopts) -o $(ppfad)$@

xbmpimage: xbmpimage.cc $(opfad)libscr.a
	$(comp) $< $(copts) $(scropts) $(xopts) $(jpgopts) -o $(ppfad)$@

xbmpview: xbmpview.cc $(opfad)libscr.a $(opfad)xscr.o $(opfad)vkbd.o $(opfad)xkbd.o
	$(comp) $< $(copts) $(opfad)xscr.o $(opfad)vkbd.o $(opfad)xkbd.o $(scropts) $(xopts) -o $(ppfad)$@

xdepth: xdepth.cc
	$(comp) $< $(copts) $(xopts) -o $(ppfad)$@

xend: xend.cc $(opfad)libscr.a $(opfad)xscr.o
	$(comp) $< $(copts) $(opfad)xscr.o $(scropts) $(xopts) -o $(ppfad)$@

xjpeg: xjpeg.cc
	$(comp) $< $(copts) $(xopts) $(jpgopts) -o $(ppfad)$@

xjpegview: xjpegview.cc $(opfad)libscr.a $(opfad)xscr.o $(opfad)vkbd.o $(opfad)xkbd.o
	$(comp) $< $(copts) $(opfad)xscr.o $(opfad)vkbd.o $(opfad)xkbd.o $(scropts) $(xopts) $(jpgopts) -o $(ppfad)$@

xkeynr: xkeynr.cc
	$(comp) $< $(copts) $(xopts) -o $(ppfad)$@

xputimage: xputimage.cc
	$(comp) $< $(copts) $(xopts) -o $(ppfad)$@

xputimageorig: xputimageorig.cc
	$(comp) $< $(copts) $(xopts) -o $(ppfad)$@

xshowkonv: xshowkonv.cc $(opfad)libscr.a $(opfad)xscr.o
	$(comp) $< $(copts) $(opfad)xscr.o $(scropts) $(xopts) -o $(ppfad)$@

xshowwav: xshowwav.cc $(opfad)libscr.a $(opfad)xscr.o $(opfad)vkbd.o $(opfad)xkbd.o
	$(comp) $< $(copts) $(opfad)xscr.o $(scropts) $(opfad)vkbd.o $(opfad)xkbd.o $(scropts) $(xopts) -o $(ppfad)$@

