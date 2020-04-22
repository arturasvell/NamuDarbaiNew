NamuDarbai : logic.o
	g++ -O3 -o NamuDarbai NamuDarbai.cpp logic.o
logic :
	g++ -c logic.cpp
clean :
	rm *.o NamuDarbai
