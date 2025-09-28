# --------------------------- Enviroment-Check ------------------------------
ifndef PLATFORM
$(error you must set PLATFORM variable (linux))
endif

ifndef CCSTANDARD
$(error you must set CCSTANDARD variable (c++11))
endif

opfad=$(HOME)/bin/$(PLATFORM)/o/
ppfad=$(HOME)/bin/$(PLATFORM)/sbin/

comp=g++

# -------------------------- Makeoptions ------------------------------------
copts=-std=$(CCSTANDARD) -Wall -Wextra -Wconversion -pedantic-errors -O2
libopts=-ljpeg -L/usr/X11R6/lib -lX11
file=xdia

all:
	$(comp) $(file).cc $(copts) $(libopts) -o $(ppfad)$(file)

clean:
	rm -f $(file)
