all: animal.o predator.o prey.o basic_funcs.o output.o app.o birth.o config.o simulation.o main.o
	g++ -lncurses -o terrarium animal.o predator.o prey.o basic_funcs.o output.o app.o birth.o config.o simulation.o main.o



main.o: main.cpp
	g++ -c main.cpp

animal.o: animal.cpp
	g++ -c animal.cpp

predator.o: predator.cpp
	g++ -c predator.cpp

prey.o: prey.cpp
	g++ -c prey.cpp

basic_funcs.o: basic_funcs.cpp
	g++ -c basic_funcs.cpp

output.o: output.cpp
	g++ -c output.cpp

app.o: app.cpp
	g++ -c app.cpp

birth.o: birth.cpp
	g++ -c birth.cpp

config.o: config.cpp
	g++ -c config.cpp

simulation.o: simulation.cpp
	g++ -c simulation.cpp



clean:
	rm *.o
