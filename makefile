NamuDarbai : logic.o
	g++ -o NamuDarbai NamuDarbai.cpp logic.o
logic :
	g++ -c logic.cpp
clean :
	rm *.o NamuDarbai
