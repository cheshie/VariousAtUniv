### Tools
## Another Option:  g++ *.cpp -o output
## Another: 

cc=g++
ldflags=-g
mf=-lm
PROGRAMS=main4

all : $(PROGRAMS)

### Generic targets

#REMARK:
#Even if you put "Stdafx.o :" generated file
#Will be "stdafx.o" -> because it's generated
#From stdafx.cpp

main4 : main.o rownanie.o rozwiazanie.o rzeczywiste.o urojone.o zespolone.o
	${cc} ${mf} -o $@ $^ 

main.o : main.cpp
	${cc} ${ldflags} -c $<

rownanie.o : rownanie.cpp
	${cc} ${ldflags} -c $<
	
rozwiazanie.o : rozwiazanie.cpp 
	${cc} ${ldflags} -c $<
	
rzeczywiste.o : rzeczywiste.cpp
	${cc} ${ldflags} -c $<
	
urojone.o : urojone.cpp
	${cc} ${ldflags} -c $<
	
zespolone.o : zespolone.cpp
	${cc} ${ldflags} -c $<
	
clean :
	@rm -f $(PROGRAMS) *.o core


# Another makefile example: 
# 
# "all" is name of the default target, running "make" without params would use 
# it
# all: executable1
# 
# for C++, replace CC (c compiler) with CXX (c++ compiler) which is used as 
# default linker
# CC=$(CXX)
# 
# tell which files should be used, .cpp -> .o make would do automatically
# executable1: file1.o file2.o
