comp=g++

prog1=trans
prog2=dif
prog3=otp
prog4=quad
prog5=perm
prog6=null

copts= -std=c++11 -Wall -Wextra -Wconversion -pedantic-errors -O2

$(prog1): $(prog1).cc
	$(comp) $< $(copts) -o $@

$(prog2): $(prog2).cc
	$(comp) $< $(copts) -o $@

$(prog3): $(prog3).cc
	$(comp) $< $(copts) -o $@

$(prog4): $(prog4).cc
	$(comp) $< $(copts) -o $@

$(prog5): $(prog5).cc
	$(comp) $< $(copts) -o $@

$(prog6): $(prog6).cc
	$(comp) $< $(copts) -o $@

clean:
	rm -f *.o $(prog1) $(prog2) $(prog3) $(prog4) $(prog5) $(prog6)
