FLAGS = -std=c++11 -Wall -g

EXEC=exec.out
SRC=main.cpp Graph.cpp

default: make_dir $(EXEC)

make_dir:
	test -d obj || mkdir obj

$(EXEC): $(SRC:%.cpp=obj/%.o)
	g++ $(FLAGS) $^ -o $@

obj/%.o: src/%.cpp
	g++ $(FLAGS) -c $< -o $@

clean:
	rm -rf obj

superclean: clean
	rm -f *.out 