# ------------ Makefile timeos -----------------------------------------------------

#-------------- Umgebung testen ----------------------------------------------------

ifndef PLATFORM
$(error you must set PLATFORM variable (linux))
endif

ifndef CCSTANDARD
$(error you must set CCSTANDARD variable (c++11))
endif

opfad=$(HOME)/bin/$(PLATFORM)/o/
ppfad=$(HOME)/bin/$(PLATFORM)/sbin/

comp=g++

# -------------------------- Make Optionen  ------------------------------------

copts=-std=$(CCSTANDARD) -Wall -Wextra -Wconversion -pedantic-errors -O2
ppfad=$(HOME)/bin/$(PLATFORM)/sbin/
opfad=$(HOME)/bin/$(PLATFORM)/o/

prog1=cpu
prog2=takt
prog3=asm
prog4=computer
prog5=
prog6=

$(prog1): $(prog1).cc
	$(comp) $< $(copts) -o $(ppfad)$(prog1)

$(prog2): $(prog2).cc
	$(comp) $< $(copts) -o $(ppfad)$(prog2)

$(prog3): $(prog3).cc
	$(comp) $< $(copts) -o $(ppfad)$(prog3)

$(prog4): $(prog4).cc
	$(comp) $< $(copts) -o $(ppfad)$(prog4)

$(prog5): $(prog5).cc
	$(comp) $< $(copts) -o $(ppfad)$(prog5)

$(prog6): $(prog6).cc
	$(comp) $< $(copts) -o $(ppfad)$(prog6)

allclean:
	rm -f $(opfad)*
	rm -f $(ppfad)*

clean:
	rm -f *.o $(ppfad)$(prog1) $(ppfad)$(prog2) $(ppfad)$(prog3) $(ppfad)$(prog4) $(ppfad)$(prog5) $(ppfad)$(prog6)
