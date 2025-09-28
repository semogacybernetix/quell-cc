# ------------ Makefile netunix -------------------------------------------

# --------------------------- Umgebung testen  ------------------------------

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

# -------------------------- Ziele ------------------------------------------

prog1=socksen
prog2=sockemp
prog3=sendip
prog4=recip
prog5=recip2
prog6=hold
prog61=reflector
prog7=floodsen
prog8=floodemp
prog9=filesen
prog10=fileemp
prog11=filesen2
prog12=fileemp2
prog13=timetest
prog14=thread

# Beispielprogramme
prog15=sendraw
prog16=empraw
prog17=transferraw
prog18=qosraw
prog19=emptest
prog20=qosdrop

$(prog15): $(prog15).cc
	$(comp) $< $(copts) -o $(ppfad)$(prog15)

$(prog16): $(prog16).cc
	$(comp) $< $(copts) -o $(ppfad)$(prog16)

$(prog17): $(prog17).cc
	$(comp) $< $(copts) -o $(ppfad)$(prog17)

$(prog18): $(prog18).cc
	$(comp) $< $(copts) -o $(ppfad)$(prog18)

$(prog19): $(prog19).cc
	$(comp) $< $(copts) -o $(ppfad)$(prog19)

$(prog20): $(prog20).cc
	$(comp) $< $(copts) -o $(ppfad)$(prog20)

rawinfo:
	gcc extern/rawinfo.c -o $(ppfad)rawinfo

sniffer:
	gcc extern/sniffer.c -o $(ppfad)sniffer


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

$(prog61): $(prog61).cc
	$(comp) $< $(copts) -o $(ppfad)$(prog61)

$(prog7): $(prog7).cc
	$(comp) $< $(copts) -o $(ppfad)$(prog7)

$(prog8): $(prog8).cc
	$(comp) $< $(copts) -o $(ppfad)$(prog8)

$(prog9): $(prog9).cc
	$(comp) $< $(copts) -lpthread -o $(ppfad)$(prog9)

$(prog10): $(prog10).cc
	$(comp) $< $(copts) -lpthread -o $(ppfad)$(prog10)

$(prog11): $(prog11).cc
	$(comp) $< $(copts) -lpthread -o $(ppfad)$(prog11)

$(prog12): $(prog12).cc
	$(comp) $< $(copts) -lpthread -o $(ppfad)$(prog12)

$(prog13): $(prog13).cc
	$(comp) $< $(copts) -lpthread -o $(ppfad)$(prog13)

$(prog14): $(prog14).cc
	$(comp) $< $(copts) -lpthread -o $(ppfad)$(prog14)

allclean:
	rm -f $(opfad)*
	rm -f $(ppfad)*

clean:
	rm -f *.o $(pfad)$(prog1) $(pfad)$(prog2) $(pfad)$(prog3) $(pfad)$(prog4)
