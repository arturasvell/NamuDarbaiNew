NamuDarbai : logic.o
	g++ -03 -o NamuDarbai NamuDarbai.cpp logic.o
logic :
	g++ -c logic.cpp
clean :
	rm *.o NamuDarbai
