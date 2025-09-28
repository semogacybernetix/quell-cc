# --------------------------- Enviroment-Check ------------------------------
ifndef PLATFORM
$(error you must set PLATFORM variable)
endif

opfad=$(HOME)/bin/$(PLATFORM)/o/
ppfad=$(HOME)/bin/$(PLATFORM)/sbin/

ifeq "$(PLATFORM)" "dos"
comp=gpp
else
comp=g++
endif

# -------------------------- Makeoptions ------------------------------------
copts=-Wall -pedantic -O2
xopts=-L/usr/X11R6/lib -lX11
scropts=-L$(opfad) -lscr

mods= sgfview

pmods= $(addprefix $(opfad), $(mods))
pobjs= $(addsuffix .o, $(pmods))

# -------------------------- Rules ------------------------------------------
$(opfad)libscr.a:
	make -C ../../cc/screen $@

$(opfad)vkbd.o:
	make -C ../../cc/keyboard $@

$(opfad)xscr.o:
	make -C ../../xwindow/screen $@

$(opfad)xkbd.o:
	make -C ../../xwindow/keyboard $@

$(opfad)%.o: %.cc
	$(comp) -c $(copts) -o $@ $<

all: $(pobjs)
	$(comp) $(pobjs) $(xopts) $(scropts) $(opfad)xscr.o -o $(ppfad)sgfview

clean:
	rm -f $(pobjs) $(ppfad)sgfview

rebuild: clean all
