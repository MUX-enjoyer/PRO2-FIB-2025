OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Wno-uninitialized -Wno-sign-compare -std=c++0x

program.exe: program.o matriu.tcc PRO2Excepcio.hh
	g++ -o program.exe program.cc $(OPCIONS)
	rm *.o

clean:
	rm *.o *.exe
	
