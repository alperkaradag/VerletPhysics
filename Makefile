all: compile

compile: 
	g++ -o main src/*.cpp -ISFML/include -LSFML/lib -lsfml-graphics -lsfml-window -lsfml-system
