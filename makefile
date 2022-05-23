

all: terrarium



## terrarium

terrarium: core/animal.o core/predator.o core/prey.o core/basic_funcs.o core/output.o core/birth.o core/simulation.o cli/main.o cli/app.o share/config.o
	g++ -o terrarium core/animal.o core/predator.o core/prey.o core/basic_funcs.o core/output.o core/birth.o core/simulation.o cli/main.o cli/app.o share/config.o

cli/main.o: cli/main.cpp
	g++ -c -o cli/main.o cli/main.cpp

cli/app.o: cli/app.cpp
	g++ -c -o cli/app.o cli/app.cpp




## core

core/animal.o: core/animal.cpp
	g++ -c -o core/animal.o core/animal.cpp

core/predator.o: core/predator.cpp
	g++ -c -o core/predator.o core/predator.cpp

core/prey.o: core/prey.cpp
	g++ -c -o core/prey.o core/prey.cpp

core/basic_funcs.o: core/basic_funcs.cpp
	g++ -c -o core/basic_funcs.o core/basic_funcs.cpp

core/output.o: core/output.cpp
	g++ -c -o core/output.o core/output.cpp

core/birth.o: core/birth.cpp
	g++ -c -o core/birth.o core/birth.cpp

core/simulation.o: core/simulation.cpp
	g++ -c -o core/simulation.o core/simulation.cpp




## share

share/config.o: share/config.cpp
	g++ -c -o share/config.o share/config.cpp




install:
	./install.sh


clean:
	rm share/*.o cli/*.o core/*.o terrarium
