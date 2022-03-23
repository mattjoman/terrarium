terrarium: main.cpp app.cpp simulation.cpp animal.cpp predator.cpp prey.cpp basic_funcs.cpp sim_funcs.cpp birth.cpp output.cpp config.cpp
	g++ -lncurses main.cpp app.cpp simulation.cpp animal.cpp predator.cpp prey.cpp basic_funcs.cpp sim_funcs.cpp birth.cpp output.cpp config.cpp


#all: terrarium
#
#terrarium: app.o simulation.o
#	g++ -o terrarium app.o simulation.o
#
#app.o: app.cpp main.cpp
#	g++ -gc app.cpp 
#
#
