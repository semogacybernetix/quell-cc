opfad=$(HOME)/bin/$(PLATFORM)/o/

ifeq "$(PLATFORM)" "dos"
comp=gpp
else
comp=g++
endif

copts=-Wall -Wextra -Wconversion -pedantic-errors -O2

mods=\
  cnet\

pmods= $(addprefix $(opfad), $(mods))
pobjs= $(addsuffix .o, $(pmods))

$(opfad)%.o: %.cc
	$(comp) -c $(copts) -o $@ $<

all: $(pobjs)

clean:
	rm -rf $(pobjs)

rebuild: clean all
