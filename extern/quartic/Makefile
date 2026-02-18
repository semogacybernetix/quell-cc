# ------------ Makefile class -------------------------------------------

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
copts=-std=$(CCSTANDARD) -Wall -Wextra -Wconversion -pedantic-errors -O2

# -------------------------- Ziele ------------------------------------------

allclean:
	rm -f $(opfad)*
	rm -f $(ppfad)*

#----------------------------------------------------------------------------------------------------------
quartictest:
	make $(ppfad)$@

$(opfad)quartic.o: quartic.cc quartic.h
	$(comp) $< -c $(copts) -o $@

$(opfad)quartictest.o: quartictest.cc quartic.h
	$(comp) $< -c $(copts) -o $@

$(ppfad)quartictest: $(opfad)quartic.o $(opfad)quartictest.o
	$(comp) $(opfad)quartictest.o $(opfad)quartic.o -o $@

#----------------------------------------------------------------------------------------------------------

